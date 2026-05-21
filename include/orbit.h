#ifndef ORBIT_H
#define ORBIT_H

#include "raylib.h"
#include <math.h>

typedef struct Elipse
{
    double eccentricity;
    double semiMajorAxis;
    double semiMinorAxis;
    double focalDistance;

    Vector2 center_position;
    Vector2 focal1;
    Vector2 focal2;

    Color color;

} Elipse;

double GetElipseSemiMinorAxis(double e, double a);

Elipse ElipseCreate(
    double eccentricity,
    double semiMajorAxis,
    Vector2 focus_position);

void ElipseDraw(Elipse *e);
double getPositionOnOrbit(
    struct Elipse *elipse,
    double theta);
#endif