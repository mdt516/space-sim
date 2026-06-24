#include <raylib.h>
#include <rlgl.h>

#include "defines.h"


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
	float sunRotationRate = 360.0f / 24.5f;

	sphere earth(EARTH_RADIUS);
	float earthRotation = 0;
	float earthRotationRate = 360.0f / 1.0f;
	float earthOrbit = 0;
	float earthOrbitRate = 360.0f / 365.0f;

	sphere moon(MOON_RADIUS);
	float moonRotation = 0;
	float moonRotationRate = 360.0f / 27.3f;
	float moonOrbit = 0;
	float moonOrbitRate = 360.0f / 27.3f;


	Camera3D cam3D;
	cam3D.position = {EARTH_SUN_DISTANCE + 30, 100, 0};
	cam3D.projection = CAMERA_PERSPECTIVE;
	cam3D.fovy = 45.0f;
	cam3D.up = {0, 1, 0};

	// main loop
	while (!WindowShouldClose())
	{
		sunRotation += sunRotationRate * GetFrameTime();
		earthRotation += earthRotationRate * GetFrameTime();
		moonRotation += moonRotationRate * GetFrameTime();

		earthOrbit += earthOrbitRate * GetFrameTime();
		moonOrbit += moonOrbitRate * GetFrameTime();


		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode3D(cam3D);

		UpdateCamera(&cam3D, CAMERA_FREE);
		DrawGrid(500, 50);

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			cam3D.target = earth.getPosition();
		}

		// transform and draw sun
		rlPushMatrix();
			rlRotatef(sunRotation, 0, 1, 0);
			DrawSphere({0, 0, 0}, sun.getRadius(), ORANGE);
		rlPopMatrix();


		// earth
		rlPushMatrix();
			rlRotatef(earthOrbit, 0, 1, 0);
			rlTranslatef(EARTH_SUN_DISTANCE + earth.getRadius() + sun.getRadius(), 0, 0);
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


		EndMode3D();
		EndDrawing();
	}


	CloseWindow();
}