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
	SetWindowState(FLAG_WINDOW_RESIZABLE);

	rlSetClipPlanes(0.1, 10000000000);

	#pragma region initSpheres
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
	cam3D.position = {900, 900, 900};
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


		#pragma region mercury
		rlPushMatrix();
			rlRotatef(mercuryOrbitAngle, 0, 1, 0);
			rlTranslatef(SUN_MERCURY_DISTANCE + sun.getRadius() + mercury.getRadius(), 0, 0);
			rlRotatef(mercuryRotationAngle, 0, 1, 0);
			DrawSphere({0, 0, 0}, mercury.getRadius(), DARKGREEN);
		rlPopMatrix();
		#pragma endregion


		#pragma region venus
		rlPushMatrix();
			rlRotatef(venusOrbitAngle, 0, 1, 0);
			rlTranslatef(SUN_VENUS_DISTANCE + sun.getRadius() + venus.getRadius(), 0, 0);
			rlRotatef(venusRotationAngle, 0, 1, 0);
			DrawSphere({0, 0, 0}, venus.getRadius(), YELLOW);
		rlPopMatrix();
		#pragma endregion


		#pragma region earth
		rlPushMatrix();
			rlRotatef(earthOrbitAngle, 0, 1, 0);
			rlTranslatef(SUN_EARTH_DISTANCE + sun.getRadius() + earth.getRadius(), 0, 0);
			rlRotatef(earthRotationAngle, 0, 1, 0);
			DrawSphere({0, 0, 0}, earth.getRadius(), BLUE);         // draw earth

			// moon
			rlPushMatrix();
				rlRotatef(moonOrbitAngle, 0, 1, 0);
				rlTranslatef(EARTH_MOON_DISTANCE + earth.getRadius() + moon.getRadius(), 0, 0);
				rlRotatef(moonRotationAngle, 0, 1, 0);
				DrawSphere({0, 0, 0}, moon.getRadius(), GRAY);       // draw moon
			rlPopMatrix();

		rlPopMatrix();
		#pragma endregion


		#pragma region mars
		rlPushMatrix();
			rlRotatef(marsOrbitAngle, 0, 1, 0);
			rlTranslatef(SUN_MARS_DISTANCE + sun.getRadius() + mars.getRadius(), 0, 0);
			rlRotatef(marsRotationAngle, 0, 1, 0);
			DrawSphere({0, 0, 0}, mars.getRadius(), RED);
		rlPopMatrix();
		#pragma endregion


		#pragma region jupiter
		rlPushMatrix();
			rlRotatef(jupiterOrbitAngle, 0, 1, 0);
			rlTranslatef(SUN_JUPITER_DISTANCE + sun.getRadius() + jupiter.getRadius(), 0, 0);
			rlRotatef(jupiterRotationAngle, 0, 1, 0);
			DrawSphere({0, 0, 0}, jupiter.getRadius(), BEIGE);
		rlPopMatrix();
		#pragma endregion


		#pragma region saturn
		rlPushMatrix();
			rlRotatef(saturnOrbitAngle, 0, 1, 0);
			rlTranslatef(SUN_SATURN_DISTANCE + sun.getRadius() + saturn.getRadius(), 0, 0);
			rlRotatef(saturnRotationAngle, 0, 1, 0);
			DrawSphere({0, 0, 0}, saturn.getRadius(), YELLOW);
		rlPopMatrix();
		#pragma endregion


		#pragma region uranus
		rlPushMatrix();
			rlRotatef(uranusOrbitAngle, 0, 1, 0);
			rlTranslatef(SUN_URANUS_DISTANCE + sun.getRadius() + uranus.getRadius(), 0, 0);
			rlRotatef(uranusRotationAngle, 0, 1, 0);
			DrawSphere({0, 0, 0}, uranus.getRadius(), SKYBLUE);
		rlPopMatrix();
		#pragma endregion


		#pragma region neptune
		rlPushMatrix();
			rlRotatef(neptuneOrbitAngle, 0, 1, 0);
			rlTranslatef(SUN_NEPTUNE_DISTANCE + sun.getRadius() + neptune.getRadius(), 0, 0);
			rlRotatef(neptuneRotationAngle, 0, 1, 0);
			DrawSphere({0, 0, 0}, neptune.getRadius(), SKYBLUE);
		rlPopMatrix();
		#pragma endregion


		EndMode3D();
		EndDrawing();
	}


	CloseWindow();
}