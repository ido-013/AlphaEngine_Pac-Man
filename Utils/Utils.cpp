#include "Utils.h"

int PosToMapX(float winWidth, float width, float x)
{
    return (x + (winWidth / 2)) / (winWidth / width);
}

int PosToMapY(float winHeight, float height, float y)
{
    return (y + (winHeight / 2)) / (winHeight / height);
}

float MapToPosX(float winWidth, float scaleX, float width, int ind)
{
    return (winWidth / width) * ind - (winWidth / 2) + (scaleX / 2);
}

float MapToPosY(float winHeight, float scaleY, float height, int ind)
{
    return (winHeight / height) * ind - (winHeight / 2) + (scaleY / 2);
}
