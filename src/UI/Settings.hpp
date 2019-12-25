#pragma once

struct Settings {
	// Camera control speed
	static const float DEFAULT_CAMERA_ROTATION_SPEED_IN_TURNS_PER_INCH;
	static float               CAMERA_ROTATION_SPEED_IN_TURNS_PER_INCH;
	static const float DEFAULT_CAMERA_TRANSLATION_SPEED_PER_INCH;
	static float               CAMERA_TRANSLATION_SPEED_PER_INCH;
	static const float DEFAULT_CAMERA_SCALE_RADIUS_PER_SCROLL;
	static float               CAMERA_SCALE_RADIUS_PER_SCROLL;

	// Camera view	
	static const float DEFAULT_CAMERA_FIELD_OF_VIEW;
	static float               CAMERA_FIELD_OF_VIEW;

	// Cursor visual
	static bool SHOW_CURSOR_THROUGH_CUBES;
};