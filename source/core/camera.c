//
// Created by strunov on 11/23/2020.
//
//
// Created by strunov on 4/21/2020.
//
#include <tonc.h>
#include "camera.h"

int cam_left, cam_top;

void cam_lookAt(int x, int y) {
    cam_left = x - SCREEN_WIDTH/2;
    cam_top = y + SCREEN_HEIGHT/2;
}

void cam_moveXY(int dx, int dy) {
    cam_left += dx;
    cam_top += dy;
}
void cam_moveX(int dx) {
    cam_left += dx;
}
void cam_moveY(int dy) {
    cam_top += dy;
}

POINT *pt_to_camera_space(struct POINT *pd, struct POINT *p) {
    pt_set(pd,
           p->x - cam_left,
           cam_top - p->y
    );
    return pd;
}

RECT *rc_to_camera_space(struct RECT *rd, struct RECT *r) {
    rc_set(rd,
           r->left - cam_left,
           cam_top - r->top,
           r->right - cam_left,
           cam_top - r->bottom
           );
    return rd;
}

int to_camera_spaceX(int x) {
    return x - cam_left;
}

int to_camera_spaceY(int y) {
    return cam_top - y;
}





