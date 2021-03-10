//
// Created by strunov on 11/23/2020.
//

#ifndef GBINDY_CAMERA_H
#define GBINDY_CAMERA_H

#include <tonc_math.h>

void cam_lookAt(int x, int y);
void cam_moveXY(int dx, int dy);
void cam_moveX(int dx);
void cam_moveY(int dy);

POINT *pt_to_camera_space(struct POINT *pd, struct POINT *p);
RECT *rc_to_camera_space(struct RECT *rd, struct RECT *r);
int to_camera_spaceX(int x);
int to_camera_spaceY(int y);

#endif //GBINDY_CAMERA_H
