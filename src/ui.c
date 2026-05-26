#include "ui.h"
#include "raylib.h"
#include "config.h"
#include <math.h>
#include <string.h>
#include "input.h"
#include "simulation.h"
#include "planet.h"
#include "newton-planet.h"
void DrawMainMenu()
{
    DrawText(TextFormat("Author's: Timofei Filip Emanuel & Bunghez Andrei"), 20, screenHeight - 100, 25, RAYWHITE);
    DrawText(TextFormat("Coordonators: Prof. Radu Simona"), 20, screenHeight - 70, 25, RAYWHITE);
    Rectangle keplerButton = {
        screenWidth / 2 - 200,
        300,
        500,
        80};

    Rectangle gravityButton = {
        screenWidth / 2 - 200,
        420,
        500,
        80};
    Rectangle newtonButton = {
        screenWidth / 2 - 200,
        540,
        500,
        80};

    Vector2 mouse = GetMousePosition();

    bool hoverKepler =
        CheckCollisionPointRec(mouse, keplerButton);

    bool hoverGravity =
        CheckCollisionPointRec(mouse, gravityButton);
    bool hoverNewton =
        CheckCollisionPointRec(mouse, newtonButton);

    DrawText(
        "GRAVICODE",
        screenWidth / 2 - 152,
        120 + sin(GetTime() * 3.0) * 10,
        70,
        WHITE);

    // Kepler Button
    DrawRectangleRec(
        keplerButton,
        hoverKepler ? DARKBLUE : BLUE);

    DrawRectangleLinesEx(
        keplerButton,
        3,
        WHITE);

    DrawText(
        "Solar System simulator",
        keplerButton.x + 80,
        keplerButton.y + 25,
        30,
        WHITE);

    // Gravity Button
    DrawRectangleRec(
        gravityButton,
        hoverGravity ? DARKGREEN : GREEN);

    DrawRectangleLinesEx(
        gravityButton,
        3,
        WHITE);

    DrawText(
        "Create solar system",
        gravityButton.x + 100,
        gravityButton.y + 25,
        30,
        WHITE);
    DrawRectangleRec(
        newtonButton,
        hoverNewton ? GRAY : LIGHTGRAY);

    DrawRectangleLinesEx(
        newtonButton,
        3,
        WHITE);

    DrawText(
        "Universal Law of Gravitation",
        newtonButton.x + 40,
        newtonButton.y + 25,
        30,
        WHITE);
    if (hoverKepler && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        scene = 1;
    }

    else if (hoverGravity && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        scene = 2;
        strcpy(inputStarMass.text, "1.989e30");
        strcpy(inputStarRadius.text, "20");

        strcpy(inputSemiMajor.text, "149.6e9");
        strcpy(inputEccentricity.text, "0.0167");
        strcpy(inputPlanetRadius.text, "6");
        strcpy(inputPlanetMass.text, "5.972e24");
    }
    else if (hoverNewton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        strcpy(inputNewtonPlanetMass.text, "");
        strcpy(inputNewtonPlanetRadius.text, "");
        newtonPlanetCount = 0;
        scene = 3;
    }
}
void showTimeScale()
{
    int time = (int)TIME_SCALE;

    int days = time / 86400;
    int hours = (time % 86400) / 3600;
    int minutes = (time % 3600) / 60;
    int seconds = time % 60;

    DrawText(
        TextFormat(
            "Time Scale: 1 simulated second = %d d %d h %d m %d s in real-time",
            days,
            hours,
            minutes,
            seconds),
        20,
        screenHeight - 50,
        15,
        GRAY);
}
void drawPresets()
{
    DrawText(TextFormat("Distance Scale: 2.5e-9 px/m"), screenWidth - 260, screenHeight - 60, 15, GRAY);
    DrawText(TextFormat("Gravitational Constant: 6.67430e-11"), screenWidth - 260, screenHeight - 30, 15, GRAY);
    DrawText(TextFormat("Press 1 -> 5 for time scale presets"), 20, screenHeight - 30, 15, GRAY);
    DrawText("[1] Real Time", 20, 20, 15, GRAY);
    DrawText("[2] 1 Day/sec", 20, 45, 15, GRAY);
    DrawText("[3] 7 Days/sec", 20, 70, 15, GRAY);
    DrawText("[4] 30 days/sec", 20, 95, 15, GRAY);
    DrawText("[5] 365 days/sec", 20, 120, 15, GRAY);
    DrawText("Press space for next planet", 20, 145, 15, GRAY);

    if (scene == 1 && planets[index_in_planets] != NULL)
        DrawText(TextFormat("Selected planet: %s", planets[index_in_planets]->name), 20, 170, 15, GRAY);
    else
        DrawText(TextFormat("Selected planet: none"), 20, 170, 15, GRAY);
}