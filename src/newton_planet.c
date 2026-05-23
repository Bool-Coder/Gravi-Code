#include "newton-planet.h"
#include "input.h"
#include "config.h"
#include "utils.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#define MAX_CUSTOM_PLANETS 20

newtonPlanet newtonPlanets[MAX_CUSTOM_PLANETS];
int newtonPlanetCount = 0;
Vector2 click_position;
Vector2 end_position;
void NewtonPlanetDraw(struct newtonPlanet *p)
{
    Vector2 s = WorldToScreen(p->position);

    DrawCircleV(s, (float)fmax(2.0, p->radius * zoom), p->color);
}
newtonPlanet createNewtonPlanet(double radius, double mass, Vector2 position, Color color)
{
    newtonPlanet new_planet;
    new_planet.radius = radius;
    new_planet.mass = mass;
    new_planet.position = position;
    new_planet.color = color;
    new_planet.velocity_x = 0;
    new_planet.velocity_y = 0;
    new_planet.orbitCount = 0;
    return new_planet;
}
void DrawOrbit(newtonPlanet *p)
{
    for (int i = 1; i < p->orbitCount; i++)
    {
        Vector2 a =
            WorldToScreen(p->orbit[i - 1]);

        Vector2 b =
            WorldToScreen(p->orbit[i]);

        DrawLineV(a, b, Fade(p->color, 0.5f));
    }
}
void CreatePlanetOnClick()
{

    if (newtonPlanetCount >= MAX_CUSTOM_PLANETS)
        return;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        Vector2 world =
            {
                (mouse.x - screenWidth / 2) /
                        (DISTANCE_SCALE * zoom) +
                    camera_position.x,

                (mouse.y - screenHeight / 2) /
                        (DISTANCE_SCALE * zoom) +
                    camera_position.y};
        click_position = mouse;
    }
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();

        DrawLine(click_position.x, click_position.y, mouse.x, mouse.y, WHITE);
        // printf("%f %f %f %f\n", click_position.x, click_position.y, world.x, world.y);
    }
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        end_position = GetMousePosition();
        Vector2 world =
            {
                (click_position.x - screenWidth / 2) /
                        (DISTANCE_SCALE * zoom) +
                    camera_position.x,

                (click_position.y - screenHeight / 2) /
                        (DISTANCE_SCALE * zoom) +
                    camera_position.y};
        double mass = atof(inputNewtonPlanetMass.text);
        double radius = atof(inputNewtonPlanetRadius.text);
        printf("%f %f", mass, radius);
        if (mass == 0)
            return;
        if (radius == 0)
            return;
        newtonPlanets[newtonPlanetCount++] = createNewtonPlanet(radius, mass, world, WHITE);
        newtonPlanets[newtonPlanetCount - 1].velocity_x = (click_position.x - end_position.x);
        newtonPlanets[newtonPlanetCount - 1].velocity_y = (click_position.y - end_position.y);
    }
}