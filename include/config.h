#ifndef CONFIG_H
#define CONFIG_H

#include "raylib.h"

extern const double G;
extern const double DISTANCE_SCALE;

extern double TIME_SCALE;
extern const int TargetFPS;

extern const double VISUAL_BOOST;
extern const float CAMERASPEED;

extern const double TIME_SCALE_PRESET_1;
extern const double TIME_SCALE_PRESET_2;
extern const double TIME_SCALE_PRESET_3;
extern const double TIME_SCALE_PRESET_4;
extern const double TIME_SCALE_PRESET_5;
extern int scene;

extern const int screenWidth;
extern const int screenHeight;

extern Vector2 camera_position;
extern float zoom;

#endif