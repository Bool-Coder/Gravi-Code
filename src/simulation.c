#include "simulation.h"
#include "config.h"
#include "planet.h"
#include "orbit.h"
#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CUSTOM_PLANETS 100
#define MAX_CUSTOM_STARS 20

Planet customPlanets[MAX_CUSTOM_PLANETS];
Elipse customOrbits[MAX_CUSTOM_PLANETS];
Planet customStars[MAX_CUSTOM_STARS];
int index_in_planets = 0;
int customPlanetCount = 0;
int customStarCount = 0;
int selectedStar = -1;

void createStar()
{
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
    {
        if (customStarCount < MAX_CUSTOM_STARS)
        {
            Vector2 mouse = GetMousePosition();
            double mass = atof(inputStarMass.text);
            double radius = atof(inputStarRadius.text);
            Vector2 world =
                {
                    (mouse.x - screenWidth / 2) /
                            (DISTANCE_SCALE * zoom) +
                        camera_position.x,

                    (mouse.y - screenHeight / 2) /
                            (DISTANCE_SCALE * zoom) +
                        camera_position.y};

            customStars[customStarCount] =
                PlanetCreate(
                    radius,
                    mass,
                    world,
                    NULL,
                    NULL,
                    YELLOW,
                    "STAR");

            selectedStar = customStarCount;

            customStarCount++;
        }
    }
}
void createPlanet()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        if (selectedStar != -1 &&
            customPlanetCount < MAX_CUSTOM_PLANETS)
        {
            double a =
                atof(inputSemiMajor.text);

            double e =
                atof(inputEccentricity.text);

            double radius =
                atof(inputPlanetRadius.text);

            double mass =
                atof(inputPlanetMass.text);

            customOrbits[customPlanetCount] =
                ElipseCreate(
                    e,
                    a,
                    customStars[selectedStar].position);
            char name[25] = "PLANET ";
            char number[25];
            sprintf(number, "%d", customPlanetCount + 1);
            strcat(name, number);
            customPlanets[customPlanetCount] =
                PlanetCreate(
                    radius,
                    mass,
                    (Vector2){0, 0},
                    &customOrbits[customPlanetCount],
                    &customStars[selectedStar],
                    SKYBLUE,
                    name);

            customPlanetCount++;
        }
    }
}

void changePlanet()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        index_in_planets++;

        if (scene == 1 && index_in_planets > 10)
            index_in_planets = 0;

        if (scene == 2 && index_in_planets >= customPlanetCount)
            index_in_planets = 0;
    }
}

void changeTimeScale()
{
    if (IsKeyDown(KEY_ONE))
        TIME_SCALE = TIME_SCALE_PRESET_1;
    if (IsKeyDown(KEY_TWO))
        TIME_SCALE = TIME_SCALE_PRESET_2;
    if (IsKeyDown(KEY_THREE))
        TIME_SCALE = TIME_SCALE_PRESET_3;
    if (IsKeyDown(KEY_FOUR))
        TIME_SCALE = TIME_SCALE_PRESET_4;
    if (IsKeyDown(KEY_FIVE))
        TIME_SCALE = TIME_SCALE_PRESET_5;
}
void updateCustomSolarSystem()
{
    createStar();
    createPlanet();
    for (int i = 0; i < customPlanetCount; i++)
    {
        PlanetUpdate(&customPlanets[i]);
    }
    if (customPlanetCount > 0)
        printf("%f\n", customPlanets[0].theta);
    if (IsKeyPressed(KEY_R))
    {
        customPlanetCount = 0;
        customStarCount = 0;
        selectedStar = -1;
    }
}

void DrawCreateSolarSystemUI()
{
    DrawText("RIGHT CLICK -> CREATE STAR", 20, 200, 20, GRAY);
    DrawText("PRESS ENTER -> CREATE PLANET", 20, 225, 20, GRAY);
    DrawText("- STAR VALUES -", 20, 310, 20, WHITE);
    DrawText("- PLANET VALUES -", 20, 490, 20, WHITE);
    DrawText(TextFormat("Press R to reset"), screenWidth - 260, screenHeight - 120, 15, GRAY);

    UpdateInputBox(&inputSemiMajor);
    UpdateInputBox(&inputEccentricity);
    UpdateInputBox(&inputPlanetRadius);
    UpdateInputBox(&inputPlanetMass);
    UpdateInputBox(&inputStarMass);
    UpdateInputBox(&inputStarRadius);
    DrawInputBox(&inputSemiMajor, "Semi Major Axis");
    DrawInputBox(&inputEccentricity, "Eccentricity");
    DrawInputBox(&inputPlanetRadius, "Planet Radius");
    DrawInputBox(&inputPlanetMass, "Planet Mass");
    DrawInputBox(&inputStarMass, "Star Mass");
    DrawInputBox(&inputStarRadius, "Star Radius");
    drawInformationCurrentPlanet();
    for (int i = 0; i < customStarCount; i++)
        PlanetDraw(&customStars[i]);

    for (int i = 0; i < customPlanetCount; i++)
    {
        ElipseDraw(&customOrbits[i]);
        PlanetDraw(&customPlanets[i]);
    }
}
void drawInformationCurrentPlanet()
{
    struct Planet *p = NULL;

    if (scene == 1)
    {
        if (planets[index_in_planets] == NULL)
            return;

        p = planets[index_in_planets];
    }

    if (scene == 2)
    {
        if (customPlanetCount <= 0)
        {
            DrawText("No custom planets created", screenWidth - 320, 20, 20, GRAY);
            return;
        }
        if (index_in_planets >= customPlanetCount)
            index_in_planets = 0;

        p = &customPlanets[index_in_planets];
    }
    if (p == NULL)
        return;
    if (p->targetElipse == NULL ||
        p->targetStar == NULL)
    {
        DrawText("No orbital data available", screenWidth - 320, 20, 20, GRAY);
        return;
    }

    DrawText(TextFormat("%s Real Orbital Period: %.2lf s", p->name, getRealOrbitalPeriod(p)), screenWidth - 450, 20, 15, GRAY);
    DrawText(TextFormat("%s Simulation Orbital Period: %.2lf s", p->name, getSimulationOrbitalPeriod(p)), screenWidth - 450, 45, 15, GRAY);
    DrawText(TextFormat("%s Aphelion Speed: %.2lf m/s", p->name, getAfelionSpeed(p)), screenWidth - 450, 70, 15, GRAY);
    DrawText(TextFormat("%s Perihelion Speed: %.2lf m/s", p->name, getPerihelionSpeed(p)), screenWidth - 450, 95, 15, GRAY);
    DrawText(TextFormat("%s Current Speed: %.2lf m/s", p->name, getCurrentSpeed(p)), screenWidth - 450, 120, 15, GRAY);

    DrawText(TextFormat("%s Mechanical Energy: %.2e J", p->name, getTotalMechanicalEnergy(p)), screenWidth - 450, 145, 15, GRAY);
}
