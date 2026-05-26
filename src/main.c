#include "raylib.h"

#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <stdio.h>
#include "config.h"
#include "planet.h"
#include "orbit.h"
#include "camera.h"
#include "ui.h"
#include "input.h"
#include "simulation.h"
#include "newton-planet.h"
#include "newton_gravity.h"

int main(void)
{
    srand(time(NULL));

    Vector2 sunPosition = (Vector2){screenWidth / 2, screenHeight / 2};
    struct Elipse mercury_orbit = ElipseCreate(0.2056, 57.9e9, sunPosition);
    struct Elipse venus_orbit = ElipseCreate(0.0068, 108.2e9, sunPosition);
    struct Elipse earth_orbit = ElipseCreate(0.0167, 149.6e9, sunPosition);
    struct Elipse mars_orbit = ElipseCreate(0.0934, 227.9e9, sunPosition);
    struct Elipse jupiter_orbit = ElipseCreate(0.0489, 7.786e11, sunPosition);
    struct Elipse saturn_orbit = ElipseCreate(0.0565, 1.4335e12, sunPosition);
    struct Elipse uranus_orbit = ElipseCreate(0.0463, 2.8725e12, sunPosition);
    struct Elipse neptune_orbit = ElipseCreate(0.0086, 4.4951e12, sunPosition);

    struct Elipse halley_comet_orbit = ElipseCreate(0.967, 2.66e12, sunPosition);

    struct Planet sun = PlanetCreate(25, 1.989e30, sunPosition, NULL, NULL, YELLOW, "SUN");
    struct Planet earth = PlanetCreate(10, 5.972e24, (Vector2){0, 0}, &earth_orbit, &sun, BLUE, "EARTH");
    struct Planet mercury = PlanetCreate(6, 3.285e23, (Vector2){0, 0}, &mercury_orbit, &sun, GRAY, "MERCURY");
    struct Planet venus = PlanetCreate(8, 4.867e24, (Vector2){0, 0}, &venus_orbit, &sun, SKYBLUE, "VENUS");
    struct Planet mars = PlanetCreate(7, 6.39e23, (Vector2){0, 0}, &mars_orbit, &sun, RED, "MARS");

    struct Planet jupiter = PlanetCreate(18, 1.898e27, (Vector2){0, 0}, &jupiter_orbit, &sun, ORANGE, "JUPITER");
    struct Planet saturn = PlanetCreate(16, 5.683e26, (Vector2){0, 0}, &saturn_orbit, &sun, LIGHTGRAY, "SATURN");
    struct Planet uranus = PlanetCreate(14, 8.681e25, (Vector2){0, 0}, &uranus_orbit, &sun, SKYBLUE, "URANUS");
    struct Planet neptune = PlanetCreate(14, 1.024e26, (Vector2){0, 0}, &neptune_orbit, &sun, BLUE, "NEPTUNE");
    struct Elipse moon_orbit = ElipseCreate(0.0549, 384400000.0, earth.position);
    struct Planet moon = PlanetCreate(3, 9.342e22, (Vector2){0, 0}, &moon_orbit, &earth, LIGHTGRAY, "MOON");

    struct Planet halley = PlanetCreate(5, 2.2e14, (Vector2){0, 0}, &halley_comet_orbit, &sun, LIGHTGRAY, "HALLEY COMET");

    planets[0] = &sun;
    planets[1] = &mercury;
    planets[2] = &venus;
    planets[3] = &earth;
    planets[4] = &mars;
    planets[5] = &jupiter;
    planets[6] = &saturn;
    planets[7] = &uranus;
    planets[8] = &neptune;
    planets[9] = &moon;
    planets[10] = &halley;

    InitWindow(screenWidth, screenHeight, "Kepler's Laws");

    SetTargetFPS(TargetFPS);

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);
        updateZoom();
        moveCamera();

        changePlanet();
        if (scene == 0)
        {
            DrawMainMenu();
            EndDrawing();
            continue;
        }

        DrawText(TextFormat("Press M for menu"), screenWidth - 260, screenHeight - 90, 15, GRAY);
        if (scene == 3)
        {
            UpdateInputBox(&inputNewtonPlanetRadius);
            UpdateInputBox(&inputNewtonPlanetMass);
            if (!inputNewtonPlanetRadius.active && !inputNewtonPlanetMass.active)
            {
                CreatePlanetOnClick();
                changeTimeScale();
            }
            showTimeScale();

            applyGravity();
            for (int i = 0; i < newtonPlanetCount; i++)
            {
                NewtonPlanetDraw(&newtonPlanets[i]);
            }

            DrawInputBox(&inputNewtonPlanetMass, "PLANET MASS");
            DrawInputBox(&inputNewtonPlanetRadius, "PLANET RADIUS");

            drawPresets();
            EndDrawing();
        }
        else if (scene == 2)
        {
            showTimeScale();

            updateCustomSolarSystem();
            DrawCreateSolarSystemUI();
            drawPresets();
            if (!inputEccentricity.active && !inputSemiMajor.active && !inputPlanetRadius.active && !inputPlanetMass.active && !inputStarRadius.active && !inputStarMass.active)
            {
                if (IsKeyPressed(KEY_R))
                {
                    customPlanetCount = 0;
                    customStarCount = 0;
                    selectedStar = -1;
                }
                changeTimeScale();
            }
            EndDrawing();
        }
        else if (scene == 1)
        {
            changeTimeScale();
            PlanetUpdate(&earth);
            PlanetUpdate(&sun);
            PlanetUpdate(&mercury);
            PlanetUpdate(&venus);
            PlanetUpdate(&mars);
            PlanetUpdate(&jupiter);
            PlanetUpdate(&saturn);
            PlanetUpdate(&uranus);
            PlanetUpdate(&neptune);
            PlanetUpdate(&halley);

            moon_orbit = ElipseCreate(0.0549, 384400000.0, earth.position);
            PlanetUpdate(&moon);

            drawPresets();
            drawInformationCurrentPlanet();

            showTimeScale();
            ElipseDraw(&earth_orbit);
            ElipseDraw(&mercury_orbit);
            ElipseDraw(&venus_orbit);
            ElipseDraw(&mars_orbit);
            ElipseDraw(&jupiter_orbit);
            ElipseDraw(&saturn_orbit);
            ElipseDraw(&uranus_orbit);
            ElipseDraw(&neptune_orbit);
            ElipseDraw(&moon_orbit);
            ElipseDraw(&halley_comet_orbit);

            PlanetDraw(&sun);
            PlanetDraw(&earth);
            PlanetDraw(&mercury);
            PlanetDraw(&venus);
            PlanetDraw(&mars);

            PlanetDraw(&jupiter);
            PlanetDraw(&saturn);
            PlanetDraw(&uranus);
            PlanetDraw(&neptune);
            PlanetDraw(&moon);
            PlanetDraw(&halley);
            EndDrawing();
            continue;
        }
    }
    CloseWindow();

    return 0;
}