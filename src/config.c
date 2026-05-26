#include "config.h"

const double G = 6.67430e-11;
const double DISTANCE_SCALE = 2.5e-9;

double TIME_SCALE = 7 * 86400;
const double TIME_SCALE_PRESET_1 = 1;
const double TIME_SCALE_PRESET_2 = 86400;
const double TIME_SCALE_PRESET_3 = 7 * 86400;
const double TIME_SCALE_PRESET_4 = 30 * 86400;
const double TIME_SCALE_PRESET_5 = 365 * 86400;

const double VISUAL_BOOST = 45.0;
const float CAMERASPEED = 20.0f;

int scene = 0;

const int screenWidth = 1200;
const int screenHeight = 880;
const int TargetFPS = 60;

Vector2 camera_position = {0, 0};

float zoom = 1.0f;