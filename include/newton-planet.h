#ifndef NEWTON_PLANET_H
#define NEWTON_PLANET_H
#include "config.h"
#include "utils.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define ORBIT_POINTS 500

typedef struct newtonPlanet
{
    double radius;
    double mass;
    Vector2 position;
    double velocity_x;
    double velocity_y;
    Vector2 orbit[ORBIT_POINTS];
    int orbitCount;
    Color color;
} newtonPlanet;

extern newtonPlanet newtonPlanets[20];
extern int newtonPlanetCount;

extern void NewtonPlanetDraw(newtonPlanet *p);

void CreatePlanetOnClick();

#endif