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
	float sunRotation = 0;

	sphere earth(EARTH_RADIUS);
	float earthRotation = 0;
	float earthOrbit = 0;

	sphere moon(MOON_RADIUS);
	float moonRotation = 0;
	float moonOrbit = 0;

	sphere mercury(MERCURY_RADIUS);
	float mercuryRotation = 0;
	float mercuryOrbit = 0;

	sphere venus(VENUS_RADIUS);
	float venusRotation = 0;
	float venusOrbit = 0;

	sphere mars(MARS_RADIUS);
	float marsRotation = 0;
	float marsOrbit = 0;

	sphere jupiter(JUPITER_RADIUS);
	float jupiterRotation = 0;
	float jupiterOrbit = 0;

	sphere saturn(SATURN_RADIUS);
	float saturnRotation = 0;
	float saturnOrbit = 0;

	sphere uranus(URANUS_RADIUS);
	float uranusRotation = 0;
	float uranusOrbit = 0;

	sphere neptune(NEPTUNE_RADIUS);
	float neptuneRotation = 0;
	float neptuneOrbvenus;

	Camera3D cam3D;
	cam3D.position = {SUN_EARTH_DISTANCE + 30, 200, 0};
	cam3D.projection = CAMERA_PERSPECTIVE;
	cam3D.fovy = 45.0f;
	cam3D.up = {0, 1, 0};

	// main loop
	while (!WindowShouldClose())
	{
		sunRotation += SUN_ROTATION_RATE * GetFrameTime();
		earthRotation += EARTH_ROTATION_RATE * GetFrameTime();
		moonRotation += MOON_ROTATION_RATE * GetFrameTime();

		earthOrbit += EARTH_ORBIT_RATE * GetFrameTime();
		moonOrbit += MOON_ORBIT_RATE * GetFrameTime();


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
			rlRotatef(sunRotation, 0, 1, 0);
			DrawSphere({0, 0, 0}, sun.getRadius(), ORANGE);
		rlPopMatrix();


		#pragma region earth
		rlPushMatrix();
			rlRotatef(earthOrbit, 0, 1, 0);
			rlTranslatef(SUN_EARTH_DISTANCE + earth.getRadius() + sun.getRadius(), 0, 0);
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
		#pragma endregion


		EndMode3D();
		EndDrawing();
	}


	CloseWindow();
}