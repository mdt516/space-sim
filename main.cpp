#include <raylib.h>
#include <rlgl.h>

#include "globals.h"


class sphere
{
public:
	sphere(float r) : radius(r), pos(0, 0, 0)
	{
		axes[0].position = pos;
		axes[1].position = pos;
		axes[2].position = pos;

		axes[0].direction = {1, 0, 0};     // x-axis
		axes[1].direction = {0, 1, 0};     // y-axis
		axes[2].direction = {0, 0, 1};     // z-axis
	}

	sphere(float x, float y, float z, float r) : pos(x, y, z), radius(r)
	{
		axes[0].position = pos;
		axes[1].position = pos;
		axes[2].position = pos;

		axes[0].direction = {1, 0, 0};     // x-axis
		axes[1].direction = {0, 1, 0};     // y-axis
		axes[2].direction = {0, 0, 1};     // z-axis
	}

	Vector3 getPosition() const { return pos; }
	float getRadius() const { return radius; }

	void drawAxes() const
	{
		DrawRay(axes[0], GREEN);
		DrawRay(axes[1], RED);
		DrawRay(axes[2], BLUE);
	}

private:
	Vector3 pos;
	float radius = 0;
	Ray axes[3];
};

int main()
{
	SetTargetFPS(60);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);

	sphere sun(SUN_RADIUS);
	float sunRotationAngle = 0;

	sphere earth(EARTH_RADIUS);
	float earthRotationAngle = 0;
	float earthOrbitAngle = 0;

	sphere moon(MOON_RADIUS);
	float moonRotationAngle = 0;
	float moonOrbitAngle = 0;

	sphere mercury(MERCURY_RADIUS);
	float mercuryRotationAngle = 0;
	float mercuryOrbitAngle = 0;

	sphere venus(VENUS_RADIUS);
	float venusRotationAngle = 0;
	float venusOrbitAngle = 0;

	sphere mars(MARS_RADIUS);
	float marsRotationAngle = 0;
	float marsOrbitAngle = 0;

	sphere jupiter(JUPITER_RADIUS);
	float jupiterRotationAngle = 0;
	float jupiterOrbitAngle = 0;

	sphere saturn(SATURN_RADIUS);
	float saturnRotationAngle = 0;
	float saturnOrbitAngle = 0;

	sphere uranus(URANUS_RADIUS);
	float uranusRotationAngle = 0;
	float uranusOrbitAngle = 0;

	sphere neptune(NEPTUNE_RADIUS);
	float neptuneRotationAngle = 0;
	float neptuneOrbitAngle = 0;
	#pragma endregion

	Camera3D cam3D;
	cam3D.position = {SUN_EARTH_DISTANCE + 30, 200, 0};
	cam3D.projection = CAMERA_PERSPECTIVE;
	cam3D.fovy = 45.0f;
	cam3D.up = {0, 1, 0};

	// main loop
	while (!WindowShouldClose())
	{
		// update rotations
		sunRotationAngle += SUN_ROTATION_RATE * GetFrameTime() * SIMULATION_SPEED;
		mercuryRotationAngle += MERCURY_ROTATION_RATE * GetFrameTime() * SIMULATION_SPEED;
		venusRotationAngle += VENUS_ROTATION_RATE * GetFrameTime() * SIMULATION_SPEED;
		earthRotationAngle += EARTH_ROTATION_RATE * GetFrameTime() * SIMULATION_SPEED;
		moonRotationAngle += MOON_ROTATION_RATE * GetFrameTime() * SIMULATION_SPEED;
		marsRotationAngle += MARS_ROTATION_RATE * GetFrameTime() * SIMULATION_SPEED;
		jupiterRotationAngle += JUPITER_ROTATION_RATE * GetFrameTime() * SIMULATION_SPEED;
		saturnRotationAngle += SATURN_ROTATION_RATE * GetFrameTime() * SIMULATION_SPEED;
		uranusRotationAngle += URANUS_ROTATION_RATE * GetFrameTime() * SIMULATION_SPEED;
		neptuneRotationAngle += NEPTUNE_ROTATION_RATE * GetFrameTime() * SIMULATION_SPEED;

		// update revolutions
		mercuryOrbitAngle += MERCURY_ORBIT_RATE * GetFrameTime() * SIMULATION_SPEED;
		venusOrbitAngle += VENUS_ORBIT_RATE * GetFrameTime() * SIMULATION_SPEED;
		earthOrbitAngle += EARTH_ORBIT_RATE * GetFrameTime() * SIMULATION_SPEED;
		moonOrbitAngle += MOON_ORBIT_RATE * GetFrameTime() * SIMULATION_SPEED;
		marsOrbitAngle += MARS_ORBIT_RATE * GetFrameTime() * SIMULATION_SPEED;
		jupiterOrbitAngle += JUPITER_ORBIT_RATE * GetFrameTime() * SIMULATION_SPEED;
		saturnOrbitAngle += SATURN_ORBIT_RATE * GetFrameTime() * SIMULATION_SPEED;
		uranusOrbitAngle += URANUS_ORBIT_RATE * GetFrameTime() * SIMULATION_SPEED;
		neptuneOrbitAngle += NEPTUNE_ORBIT_RATE * GetFrameTime() * SIMULATION_SPEED;


		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode3D(cam3D);

		UpdateCamera(&cam3D, CAMERA_FREE);
		DrawGrid(500, 50);

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			cam3D.target = {0, 0, 0};
		}



		// transform and draw sun
		rlPushMatrix();
			rlRotatef(sunRotationAngle, 0, 1, 0);
			DrawSphere({0, 0, 0}, sun.getRadius(), ORANGE);
		rlPopMatrix();


		#pragma region earth
		rlPushMatrix();
			rlRotatef(earthOrbit, 0, 1, 0);
			rlTranslatef(SUN_EARTH_DISTANCE + sun.getRadius()  + earth.getRadius(), 0, 0);
			rlRotatef(earthRotation, 0, 1, 0);

			DrawSphere({0, 0, 0}, earth.getRadius(), BLUE);         // draw earth

			// moon
			rlPushMatrix();
				rlRotatef(moonOrbit, 0, 1, 0);
				rlTranslatef(EARTH_MOON_DISTANCE + earth.getRadius() + moon.getRadius(), 0, 0);
				rlRotatef(moonRotation, 0, 1, 0);

				DrawSphere({0, 0, 0}, moon.getRadius(), GRAY);       // draw moon
			rlPopMatrix();

			rlPopMatrix();

		rlPopMatrix();
		#pragma endregion


		EndMode3D();
		EndDrawing();
	}


	CloseWindow();
}