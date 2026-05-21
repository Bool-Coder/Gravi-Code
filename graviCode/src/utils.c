#include "utils.h"
#include "config.h"

Vector2 WorldToScreen(Vector2 world)
{
    Vector2 screen;

    screen.x =
        (world.x - camera_position.x) * DISTANCE_SCALE * zoom + screenWidth / 2;

    screen.y =
        (world.y - camera_position.y) * DISTANCE_SCALE * zoom + screenHeight / 2;

    return screen;
}