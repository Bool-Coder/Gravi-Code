#include "planet.h"
#include "config.h"
#include "utils.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
Planet *planets[20];
Planet PlanetCreate(
    double radius,
    double mass,
    Vector2 position,
    Elipse *targetElipse,
    Planet *targetStar,
    Color color,
    char name[])
{
    Planet p;

    p.radius = radius;
    p.mass = mass;
    p.position = position;

    p.targetElipse = targetElipse;
    p.targetStar = targetStar;

    p.color = color;

    strcpy(p.name, name);

    return p;
}

void PlanetUpdate(struct Planet *p)
{
    if (p->targetElipse == NULL || p->targetStar == NULL)
        return;
    double dt = GetFrameTime() * TIME_SCALE;

    double r_physics = getPositionOnOrbit(p->targetElipse, p->theta);
    double r_render = r_physics;
    if (r_render * DISTANCE_SCALE < 10)
        r_render = r_render * VISUAL_BOOST;
    double v = sqrt(
        G * p->targetStar->mass *
        (2.0 / r_physics - 1.0 / p->targetElipse->semiMajorAxis));

    double omega = v / r_physics;
    p->theta += omega * dt;
    if (p->theta > 2 * PI)
        p->theta -= 2 * PI;
    Vector2 focus = p->targetElipse->focal1;
    p->position.x = focus.x + r_render * cos(p->theta);
    p->position.y = focus.y + r_render * sin(p->theta);
}

void PlanetDraw(struct Planet *p)
{
    Vector2 s = WorldToScreen(p->position);

    DrawCircleV(s, (float)fmax(2.0, p->radius * zoom), p->color);

    DrawText(p->name, s.x + 10, s.y + 10, 20, GRAY);
}
double getPerihelionSpeed(struct Planet *p)
{
    return sqrt((G * p->targetStar->mass / p->targetElipse->semiMajorAxis) * (1.0f + p->targetElipse->eccentricity) / (1.0f - p->targetElipse->eccentricity));
}

double getAfelionSpeed(struct Planet *p)
{
    return sqrt((G * p->targetStar->mass / p->targetElipse->semiMajorAxis) * (1.0f - p->targetElipse->eccentricity) / (1.0f + p->targetElipse->eccentricity));
}

double getRealOrbitalPeriod(struct Planet *p)
{
    double a = p->targetElipse->semiMajorAxis;
    double M = p->targetStar->mass;

    return 2.0 * PI * sqrt((a * a * a) / (G * M));
}
double getSimulationOrbitalPeriod(struct Planet *p)
{
    return getRealOrbitalPeriod(p) / TIME_SCALE;
}
double getCurrentSpeed(struct Planet *p)
{
    double r = getPositionOnOrbit(p->targetElipse, p->theta);
    double v = sqrt(
        G * p->targetStar->mass *
        (2.0 / r - 1.0 / p->targetElipse->semiMajorAxis));
    return v;
}

double getTotalMechanicalEnergy(struct Planet *p)
{
    return -((G * p->mass * p->targetStar->mass) / (2 * p->targetElipse->semiMajorAxis));
}