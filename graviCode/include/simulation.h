#ifndef SIMULATION_H
#define SIMULATION_H

extern int customPlanetCount;
extern int customStarCount;
extern int selectedStar;
extern int index_in_planets;

void updateCustomSolarSystem();
void DrawCreateSolarSystemUI();
void changePlanet();
void changeTimeScale();
void drawInformationCurrentPlanet();

#endif