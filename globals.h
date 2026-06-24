#pragma once

// window info
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const char* TITLE = "space-sim";

const float SIMULATION_SPEED = 0.2f;

// radii in km
const float SUN_RADIUS = 109.0f;
const float EARTH_RADIUS = 6.378f;
const float MOON_RADIUS = 1.0f;
const float MERCURY_RADIUS = 2439.5f;
const float VENUS_RADIUS = 6052.0f;
const float MARS_RADIUS = 3396.0f;
const float JUPITER_RADIUS = 71492.0f;
const float SATURN_RADIUS = 60268.0f;
const float URANUS_RADIUS = 25559.0f;
const float NEPTUNE_RADIUS = 24764.0f;

// 1 AU in km
const float ASTRONOMICAL_UNIT = 149597870.7f;

const float EARTH_MOON_DISTANCE = 0.0026343112f         *    ASTRONOMICAL_UNIT;
const float SUN_EARTH_DISTANCE = 1.0f                   *    ASTRONOMICAL_UNIT;
const float SUN_MERCURY_DISTANCE = 0.387f               *    ASTRONOMICAL_UNIT;
const float SUN_VENUS_DISTANCE = 0.723f                 *    ASTRONOMICAL_UNIT;
const float SUN_MARS_DISTANCE = 1.52f                   *    ASTRONOMICAL_UNIT;
const float SUN_JUPITER_DISTANCE = 5.2f                 *    ASTRONOMICAL_UNIT;
const float SUN_SATURN_DISTANCE = 9.5f                  *    ASTRONOMICAL_UNIT;
const float SUN_URANUS_DISTANCE = 19.2f                 *    ASTRONOMICAL_UNIT;
const float SUN_NEPTUNE_DISTANCE = 30.1f                *    ASTRONOMICAL_UNIT;

// time it takes to complete a rotation in (Earth) days
const float SUN_ROTATION_RATE = 360.0f / 24.5f;
const float EARTH_ROTATION_RATE = 360.0f / 1.0f;
const float MOON_ROTATION_RATE = 360.0f / 27.3f;
// todo define more rotation rates

// time it takes for them to orbit their celestial body in (Earth) days
const float MOON_ORBIT_RATE = 360.0f / 27.3f;
const float EARTH_ORBIT_RATE = 360.0f / 365.0f;
const float MERCURY_ORBIT_RATE = 360.0f / 88.0f;
const float VENUS_ORBIT_RATE = 360.0f / 225.0f;
const float MARS_ORBIT_RATE = 360.0f / 687.0f;
const float JUPITER_ORBIT_RATE = 360.0f / 4333.0f;
const float SATURN_ORBIT_RATE = 360.0f / 10759.0f;
const float URANUS_ORBIT_RATE = 360.0f / 30687.0f;
const float NEPTUNE_ORBIT_RATE = 360.0f / 60190.0f;