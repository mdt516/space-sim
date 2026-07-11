#pragma once

// window info
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const char* TITLE = "space-sim";

// controls
const float CAMERA_MOVE_SPEED = 10.0f;
const float MOUSE_SENSITIVITY = 0.05f;
const float SPEED_MODIFIER = 100.0f;

// simulation settings
const float SIMULATION_SPEED = 1.0f;
const int ORBIT_PATH_SEGMENTS = 100;

const float DISTANCE_DOWNSCALE_FACTOR = 10;
const float PLANET_SCALE_FACTOR = 100;
const float SUN_SCALE_FACTOR = 10;


// radii in km
const float SUN_RADIUS = 695700.0f           *        SUN_SCALE_FACTOR;
const float MERCURY_RADIUS = 2439.7f         *        PLANET_SCALE_FACTOR;
const float VENUS_RADIUS = 6051.8f           *        PLANET_SCALE_FACTOR;
const float EARTH_RADIUS = 6378.0f           *        PLANET_SCALE_FACTOR;
const float MOON_RADIUS = 1373.5f            *        PLANET_SCALE_FACTOR;
const float MARS_RADIUS = 3396.0f            *        PLANET_SCALE_FACTOR;
const float JUPITER_RADIUS = 71492.0f        *        PLANET_SCALE_FACTOR;
const float SATURN_RADIUS = 60268.0f         *        PLANET_SCALE_FACTOR;
const float URANUS_RADIUS = 25559.0f         *        PLANET_SCALE_FACTOR;
const float NEPTUNE_RADIUS = 24764.0f        *        PLANET_SCALE_FACTOR;

// 1 AU in km
const float ASTRONOMICAL_UNIT = 149597870.7f;

const float SUN_MERCURY_DISTANCE = 0.387f               *    ASTRONOMICAL_UNIT   /      DISTANCE_DOWNSCALE_FACTOR;
const float SUN_VENUS_DISTANCE = 0.723f                 *    ASTRONOMICAL_UNIT   /      DISTANCE_DOWNSCALE_FACTOR;
const float SUN_EARTH_DISTANCE = 1.0f                   *    ASTRONOMICAL_UNIT   /      DISTANCE_DOWNSCALE_FACTOR;
const float EARTH_MOON_DISTANCE = 0.0026343112f         *    ASTRONOMICAL_UNIT   /      DISTANCE_DOWNSCALE_FACTOR;
const float SUN_MARS_DISTANCE = 1.52f                   *    ASTRONOMICAL_UNIT   /      DISTANCE_DOWNSCALE_FACTOR;
const float SUN_JUPITER_DISTANCE = 5.2f                 *    ASTRONOMICAL_UNIT   /      DISTANCE_DOWNSCALE_FACTOR;
const float SUN_SATURN_DISTANCE = 9.5f                  *    ASTRONOMICAL_UNIT   /      DISTANCE_DOWNSCALE_FACTOR;
const float SUN_URANUS_DISTANCE = 19.2f                 *    ASTRONOMICAL_UNIT   /      DISTANCE_DOWNSCALE_FACTOR;
const float SUN_NEPTUNE_DISTANCE = 30.1f                *    ASTRONOMICAL_UNIT   /      DISTANCE_DOWNSCALE_FACTOR;

// time it takes to complete a rotation in (Earth) days
const float SUN_ROTATION_RATE = 360.0f / 24.5f;
const float MERCURY_ROTATION_RATE = 360.0f / 58.6f;
const float VENUS_ROTATION_RATE = 360.0f / 243.0f;
const float EARTH_ROTATION_RATE = 360.0f / 1.0f;
const float MOON_ROTATION_RATE = 360.0f / 27.3f;
const float MARS_ROTATION_RATE = 360.0f / 1.0277791667f;
const float JUPITER_ROTATION_RATE = 360.0f / 0.41667f;
const float SATURN_ROTATION_RATE = 360.0f / 0.4375f;
const float URANUS_ROTATION_RATE = 360.0f / 0.71875f;
const float NEPTUNE_ROTATION_RATE = 360.0f / 0.671875f;

// time it takes for them to orbit their celestial body in (Earth) days
const float MERCURY_ORBIT_RATE = 360.0f / 88.0f;
const float VENUS_ORBIT_RATE = 360.0f / 225.0f;
const float EARTH_ORBIT_RATE = 360.0f / 365.0f;
const float MOON_ORBIT_RATE = 360.0f / 27.3f;
const float MARS_ORBIT_RATE = 360.0f / 687.0f;
const float JUPITER_ORBIT_RATE = 360.0f / 4333.0f;
const float SATURN_ORBIT_RATE = 360.0f / 10759.0f;
const float URANUS_ORBIT_RATE = 360.0f / 30687.0f;
const float NEPTUNE_ORBIT_RATE = 360.0f / 60190.0f;