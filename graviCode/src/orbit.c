#include "orbit.h"
#include "config.h"
#include <math.h>
#include "utils.h"

double GetElipseSemiMinorAxis(double e, double a)
{
    return a * sqrt(1 - e * e);
}

Elipse ElipseCreate(
    double eccentricity,
    double semiMajorAxis,
    Vector2 focus_position)
{
    Elipse p;

    p.eccentricity = eccentricity;
    p.semiMajorAxis = semiMajorAxis;

    p.semiMinorAxis =
        GetElipseSemiMinorAxis(
            eccentricity,
            semiMajorAxis);

    p.focalDistance =
        semiMajorAxis * eccentricity;

    p.focal1 = focus_position;

    return p;
}

void ElipseDraw(struct Elipse *e)
{
    Vector2 prev = {0};

    for (int i = 0; i <= 360; i++)
    {
        double theta = i * DEG2RAD;
        double r_render = (e->semiMajorAxis * (1 - e->eccentricity * e->eccentricity)) / (1 + e->eccentricity * cos(theta));
        if (r_render * DISTANCE_SCALE < 10)
            r_render = r_render * VISUAL_BOOST;
        Vector2 p = {
            e->focal1.x + r_render * cos(theta),
            e->focal1.y + r_render * sin(theta)};
        Vector2 s = WorldToScreen(p);
        if (i > 0)
            DrawLineV(prev, s, WHITE);
        prev = s;
    }
}
double getPositionOnOrbit(
    Elipse *elipse,
    double theta)
{
    return (
               elipse->semiMajorAxis *
               (1 - elipse->eccentricity *
                        elipse->eccentricity)) /
           (1 +
            elipse->eccentricity *
                cos(theta));
}