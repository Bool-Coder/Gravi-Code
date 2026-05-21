#include "camera.h"
#include "config.h"
#include "raylib.h"

void moveCamera()
{
    double speed = CAMERASPEED / (DISTANCE_SCALE * zoom);

    if (IsKeyDown(KEY_RIGHT))
        camera_position.x += speed;
    if (IsKeyDown(KEY_LEFT))
        camera_position.x -= speed;

    if (IsKeyDown(KEY_UP))
        camera_position.y -= speed;
    if (IsKeyDown(KEY_DOWN))
        camera_position.y += speed;
    if (IsKeyPressed(KEY_M))
        scene = 0;
}

void updateZoom()
{
    float wheel = GetMouseWheelMove();

    if (wheel != 0)
    {
        Vector2 mouse = GetMousePosition();

        float oldZoom = zoom;

        zoom += wheel * 0.01f;

        if (zoom < 0.1f)
            zoom = 0.1f;

        if (zoom > 20.0f)
            zoom = 20.0f;

        float zoomFactor = zoom / oldZoom;

        camera_position.x =
            mouse.x - (mouse.x - camera_position.x) * zoomFactor;

        camera_position.y =
            mouse.y - (mouse.y - camera_position.y) * zoomFactor;
    }
}