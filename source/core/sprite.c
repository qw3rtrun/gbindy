//
// Created by strunov on 4/21/2020.
//
#include <tonc.h>
#include "sprite.h"
#include "camera.h"

void sprite_load(SPRITE *sprite, SPRITE_SIZE size, IMG_DATA *data, u8 palBank, u8 baseTid) {
    sprite->size = size;
    sprite->data = data;
    sprite->baseTid = baseTid;
    sprite->palBank = palBank;
    memcpy16(&pal_obj_bank[palBank], data->palSrc, data->palLen / 2);
    memcpy16(&tile_mem_obj[0][baseTid], data->tilesSrc, data->tilesLen / 2);
}

void object_init(OBJECT *obj, OBJ_ATTR *attrs, SPRITE *sprite, u8 layer) {
    obj->sprite = sprite;
    obj->hidden = false;
    obj->objAttr = attrs;
    obj->position.bottom = 0;
    obj->position.top = 7;
    obj->position.left = 0;
    obj->position.right = 7;
    obj->hflip = false;
    obj->vflip = false;
    obj->layer = layer;
}

void object_move(OBJECT *obj, int dx, int dy) {
    rc_move(&obj->position, dx, dy);
}

void object_render(OBJECT *obj) {
    obj_set_attr(obj->objAttr,
                 ATTR0_BUILD(to_camera_spaceY(obj->position.top), obj->sprite->size.shape, ATTR0_4BPP, obj->hidden, 0, 0, 0),
                 ATTR1_BUILDR(to_camera_spaceX(obj->position.left), obj->sprite->size.size, obj->hflip, obj->vflip),
                 ATTR2_BUILD(obj->sprite->baseTid, obj->sprite->palBank, obj->layer));
}