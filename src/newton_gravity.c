#include "newton-planet.h"
#include "utils.h"
#include <math.h>
#include "stdio.h"
#include "config.h"
const double GRAVITATIONAL_CONSTANT = 50000;

void applyGravity()
{
    float dt = GetTime() * TIME_SCALE;

    for (int i = 0; i < newtonPlanetCount; i++)
    {
        if (newtonPlanets[i].orbitCount < ORBIT_POINTS)
        {
            newtonPlanets[i].orbit[newtonPlanets[i].orbitCount++] = newtonPlanets[i].position;
        }
        for (int j = i + 1; j < newtonPlanetCount; j++)
        {
            double dx = newtonPlanets[j].position.x - newtonPlanets[i].position.x;
            double dy = newtonPlanets[j].position.y - newtonPlanets[i].position.y;

            double distance = sqrt(dx * dx + dy * dy);

            double softening = 10.0;
            double denom = (distance * distance) + softening * softening;
            double F =
                GRAVITATIONAL_CONSTANT *
                (newtonPlanets[i].mass * newtonPlanets[j].mass) /
                denom;

            double angle = atan2(dy, dx);

            double fx = F * cos(angle);
            double fy = F * sin(angle);

            newtonPlanets[i].velocity_x += (fx / newtonPlanets[i].mass) * dt;
            newtonPlanets[i].velocity_y += (fy / newtonPlanets[i].mass) * dt;

            newtonPlanets[j].velocity_x -= (fx / newtonPlanets[j].mass) * dt;
            newtonPlanets[j].velocity_y -= (fy / newtonPlanets[j].mass) * dt;
        }
    }

    for (int i = 0; i < newtonPlanetCount; i++)
    {
        newtonPlanets[i].position.x += newtonPlanets[i].velocity_x * dt;
        newtonPlanets[i].position.y += newtonPlanets[i].velocity_y * dt;
        printf("%f %f\n", newtonPlanets[i].position.x, newtonPlanets[i].position.y);
    }
}