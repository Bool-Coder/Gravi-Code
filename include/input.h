#ifndef INPUT_H
#define INPUT_H

#include "raylib.h"
#include <stdbool.h>

typedef struct InputBox
{
    Rectangle bounds;
    char text[64];
    int letterCount;
    bool active;

} InputBox;

extern InputBox inputStarRadius;
extern InputBox inputStarMass;

extern InputBox inputSemiMajor;
extern InputBox inputEccentricity;
extern InputBox inputPlanetRadius;
extern InputBox inputPlanetMass;
extern InputBox inputNewtonPlanetMass;
extern InputBox inputNewtonPlanetRadius;
void UpdateInputBox(InputBox *box);

void DrawInputBox(
    InputBox *box,
    const char *label);

#endif