#include "Settings.hpp"

// Camera controls speed
const float Settings::DEFAULT_CAMERA_ROTATION_SPEED_IN_TURNS_PER_INCH = 0.05f;
const float Settings::DEFAULT_CAMERA_TRANSLATION_SPEED_PER_INCH       = 0.07f;
const float Settings::DEFAULT_CAMERA_SCALE_RADIUS_PER_SCROLL          = 0.9f;
// Camera view
const float Settings::DEFAULT_CAMERA_FIELD_OF_VIEW = 0.79f;
// Cursor visual
bool Settings::SHOW_CURSOR_THROUGH_CUBES = false;

//
float Settings::CAMERA_ROTATION_SPEED_IN_TURNS_PER_INCH = DEFAULT_CAMERA_ROTATION_SPEED_IN_TURNS_PER_INCH;
float Settings::CAMERA_TRANSLATION_SPEED_PER_INCH       = DEFAULT_CAMERA_TRANSLATION_SPEED_PER_INCH;
float Settings::CAMERA_SCALE_RADIUS_PER_SCROLL          = DEFAULT_CAMERA_SCALE_RADIUS_PER_SCROLL;
float Settings::CAMERA_FIELD_OF_VIEW                    = DEFAULT_CAMERA_FIELD_OF_VIEW;