#include "utils.h"
#include "config.h"
#include "math.h"

Vector2 WorldToScreen(Vector2 world)
{
    Vector2 screen;

    screen.x =
        (world.x - camera_position.x) * DISTANCE_SCALE * zoom + screenWidth / 2;

    screen.y =
        (world.y - camera_position.y) * DISTANCE_SCALE * zoom + screenHeight / 2;

    return screen;
}
double getEuclidianDistance(Vector2 a, Vector2 b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}