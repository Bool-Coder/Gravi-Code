#ifndef PLANET_H
#define PLANET_H

#include "raylib.h"
#include "orbit.h"

typedef struct Planet
{
    double radius;
    double mass;
    double theta;

    Elipse *targetElipse;
    struct Planet *targetStar;

    Vector2 position;

    char name[20];

    Color color;

} Planet;

extern Planet *planets[20];

Planet PlanetCreate(
    double radius,
    double mass,
    Vector2 position,
    Elipse *targetElipse,
    Planet *targetStar,
    Color color,
    char name[]);

void PlanetUpdateKepler(Planet *p);

void PlanetDraw(Planet *p);
double getPerihelionSpeed(Planet *p);

double getAfelionSpeed(Planet *p);

double getRealOrbitalPeriod(Planet *p);

double getSimulationOrbitalPeriod(Planet *p);

double getCurrentSpeed(Planet *p);

double getTotalMechanicalEnergy(Planet *p);
#endif