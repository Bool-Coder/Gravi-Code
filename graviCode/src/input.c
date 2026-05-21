#include "input.h"

InputBox inputStarRadius =
    {
        {20, 360, 250, 40},
        "",
        0,
        false};

InputBox inputStarMass =
    {
        {20, 430, 250, 40},
        "",
        0,
        false};

InputBox inputSemiMajor =
    {
        {20, 550, 250, 40},
        "",
        0,
        false};

InputBox inputEccentricity =
    {
        {20, 620, 250, 40},
        "",
        0,
        false};

InputBox inputPlanetRadius =
    {
        {20, 690, 250, 40},
        "",
        0,
        false};

InputBox inputPlanetMass =
    {
        {20, 760, 250, 40},
        "",
        0,
        false};
void UpdateInputBox(struct InputBox *box)
{
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        box->active = CheckCollisionPointRec(mouse, box->bounds);
    }

    if (box->active)
    {
        int key = GetCharPressed();

        while (key > 0)
        {
            if ((key >= 32) &&
                (key <= 125) &&
                (box->letterCount < 63))
            {
                box->text[box->letterCount] = (char)key;
                box->letterCount++;
                box->text[box->letterCount] = '\0';
            }

            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            if (box->letterCount > 0)
            {
                box->letterCount--;
                box->text[box->letterCount] = '\0';
            }
        }
    }
}

void DrawInputBox(struct InputBox *box, const char *label)
{
    DrawText(
        label,
        box->bounds.x,
        box->bounds.y - 25,
        20,
        WHITE);

    DrawRectangleRec(
        box->bounds,
        box->active ? DARKBLUE : DARKGRAY);

    DrawRectangleLinesEx(
        box->bounds,
        2,
        WHITE);

    DrawText(
        box->text,
        box->bounds.x + 10,
        box->bounds.y + 10,
        20,
        WHITE);
}