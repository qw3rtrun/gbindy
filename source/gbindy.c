//
// Created by strunov on 11/17/2020.
//
#include <tonc.h>
#include <tonc_math.h>
#include "player.h"
#include "land.h"
#include "bg.h"
#include "core/sprite.h"

void physics(OBJECT *obj, BGC * bgc) {
    if (bgc_detectCollision(bgc, obj) != 0) {
        object_move(obj, 0, 1);
    }
}

int main() {
    bool running = true;
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D;
    OBJ_ATTR obj_buffer[128];
    oam_init(obj_buffer, 128);

    IMG_DATA playerImg = {
            .palLen = playerPalLen,
            .palSrc = playerPal,
            .tilesLen = playerTilesLen,
            .tilesSrc = playerTiles
    };
    SPRITE playerSprite;
    SPRITE_SIZE playerSize = SPRITE_SIZE_8x8;
    OBJ_ATTR *playerAttr = obj_buffer;
    OBJECT player;
    sprite_load(&playerSprite, playerSize, &playerImg, 0, 0);
    object_init(&player, playerAttr, &playerSprite, 0);

    BGC land;
    bg_init((BG *) &land, 0, landPalLen, landPal, landTilesLen, landTiles, landMapLen, landMap, 0, 30, 0);
    land.collisionSrc = &landCollision;
    land.collisionLen = landCollisionLen;

    cam_lookAt(0, 0);

    while (running) {
        key_poll();
        if (key_is_down(KEY_L)) {
            cam_moveXY(key_tri_horz(), -key_tri_vert());
        } else {
            object_move(&player, key_tri_horz(), -key_tri_vert());
            if (key_tri_vert() == 0) {
                physics(&player, &land);
            }
        }

        bg_render(&land);
        object_render(&player);

        oam_copy(oam_mem, obj_buffer, 1);
        vid_vsync();
    }

    return 0;
}