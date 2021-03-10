//
// Created by strunov on 4/21/2020.
//

#ifndef GBINDY_BG_H
#define GBINDY_BG_H

#include <tonc.h>
#include "core/camera.h"
#include "core/sprite.h"

typedef struct BG {
    u8 ind;
    u16 top;
    u16 left;
    u8 palLen;
    void *palSrc;
    u16 tilesLen;
    void *tilesSrc;
    u16 mapLen;
    void *mapSrc;
} BG;

typedef struct BGC {
    BG bg;
    u16 collisionLen;
    void* collisionSrc;
} BGC;

void bg_init(BG *bg, int ind, u8 palLen, void *palSrc, u16 tilesLen, void *tilesSrc, u16 mapLen, void *mapSrc,
             u8 cbb, u8 sbb, u8 layer) {
    bg->ind = ind;
    bg->top = 0;
    bg->left = 0;
    bg->palLen = palLen;
    bg->palSrc = palSrc;
    bg->tilesLen = tilesLen;
    bg->tilesSrc = tilesSrc;
    bg->mapLen = mapLen;
    bg->mapSrc = mapSrc;

    REG_BG0CNT = BG_CBB(cbb) | BG_4BPP | BG_SBB(sbb) | BG_REG_32x32 | BG_PRIO(layer);
    memcpy16(pal_bg_mem, palSrc, palLen);
    memcpy16(&tile_mem[cbb], tilesSrc, tilesLen);
    memcpy16(&se_mem[sbb], mapSrc, mapLen);
}

void bg_move(BG *bg, int dx, int dy) {
    bg->left += dx;
    bg->top += dy;
}

int bg_hSize(BG *bg) {
    return 32;
}

int bg_vSize(BG *bg) {
    return 32;
}

int to_bg_spaceX(int x, BG *bg) {
    return x - bg->left;
}

int to_bg_spaceY(int y, BG *bg) {
    return bg->top - y;
}

void bg_render(BG *bg) {
    switch (bg->ind) {
        case 0 :
            REG_BG0HOFS = -to_camera_spaceX(bg->left);
            REG_BG0VOFS = -to_camera_spaceY(bg->top);
            break;
        case 1:
            REG_BG1HOFS = -to_camera_spaceX(bg->left);
            REG_BG1VOFS = -to_camera_spaceY(bg->top);
            break;
        case 2:
            REG_BG2HOFS = -to_camera_spaceX(bg->left);
            REG_BG2VOFS = -to_camera_spaceY(bg->top);
            break;
    }
}

int bgc_collision(BGC *bgc, int line, int tile) {
    u16 tileOffset = line * bg_hSize((BG *) bgc) + tile;
    if (tileOffset > bgc->collisionLen) {
        return 0;
    }
    u8* collisions = (u8*) bgc->collisionSrc;
    return collisions[tileOffset];
}

int bgc_detectCollision(BGC *bgc, OBJECT *obj) {
    BG *bg = (BG *) bgc;
    int top = to_bg_spaceY(obj->position.top, bg);
    int left = to_bg_spaceX(obj->position.left, bg);
    int bottom = to_bg_spaceY(obj->position.bottom, bg);
    int right = to_bg_spaceX(obj->position.right, bg);

    int topLine = top >> 3;
    int bottomLine = bottom >> 3;
    int leftTile = left >> 3;
    int rightTile = right >> 3;

    for (int y = topLine; y <= bottomLine; y++) {
        for (int x = leftTile; x <= rightTile; x++) {
            int tileY = y >= 0 ? (y % 32) : 32 + (y % 32);
            int tileX = x >= 0 ? (x % 32) : 32 + (x % 32);
//            if (tileY == 1 || tileX == 1) {
//                return  1;
//            }
            int collision = bgc_collision(bgc, tileY, tileX);
            if (collision != 0) {
                return collision;
            }
        }
    }
    return 0;
}

#endif //GBINDY_LAND_H
