//
// Created by strunov on 4/21/2020.
//

#ifndef GBINDY_SPRITE_H
#define GBINDY_SPRITE_H

#include <tonc.h>

/*
shape\size	00	    01	    10	    11
00	        8x8	    16x16	32x32	64x64
01	        16x8	32x8	32x16	64x32
10	        8x16	8x32	16x32	32x64
 */

typedef struct SPRITE_SIZE {
    u16 shape;
    u16 size;
} SPRITE_SIZE;

#define SPRITE_SIZE_8x8 { .shape = ATTR0_SQUARE, .size = ATTR1_SIZE_8x8 }
// todo

typedef struct IMG_DATA {
    const void *palSrc;
    const u8 palLen;
    const void *tilesSrc;
    const u16 tilesLen;
} IMG_DATA;

typedef struct SPRITE {
    struct SPRITE_SIZE size;
    IMG_DATA *data;
    u8 palBank;
    u8 baseTid;
} SPRITE;

typedef struct OBJECT {
    SPRITE *sprite;
    bool hidden;
    OBJ_ATTR *objAttr;
    RECT position;
    bool hflip;
    bool vflip;
    u8 layer;
} OBJECT;

void sprite_load(SPRITE *sprite, SPRITE_SIZE size, IMG_DATA *data, u8 palBank, u8 baseTid);

void object_init(OBJECT *obj, OBJ_ATTR *attrs, SPRITE *sprite, u8 layer);

void object_move(OBJECT *obj, int dx, int dy);

void object_render(OBJECT *obj);

#endif //GBINDY_SPRITE_H
