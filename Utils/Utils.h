#pragma once

int PosToMapX(float winWidth, float width, float x);
int PosToMapY(float winWidth, float height, float y);
float MapToPosX(float winWidth, float scaleX, float width, int ind);
float MapToPosY(float winHeight, float scaleY, float height, int ind);