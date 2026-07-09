#include <raylib.h>
#include <rlgl.h>

#include <deque>
#include <cmath>
#include <iostream>

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

	void setPosition(float x, float z)
	{
		pos = {x, pos.y, z};
	}

	void setPosition(float x, float y, float z)
	{
		pos = {x, y, z};
	}

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

// used to track the position of the camera
struct localCam3DStats
{
	Vector3 movement = {0, 0, 0};
	Vector3 orientation = {0, 0, 0};
};

int main()
{
	bool debugOverlay = false;
	int mouseWheelMod = 0;

	SetTargetFPS(60);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
	SetWindowState(FLAG_WINDOW_RESIZABLE);

	rlSetClipPlanes(0.1, 10000000000000000000);

	#pragma region initSpheres
	sphere sun(SUN_RADIUS);
	float sunRotationAngle = 0;

	sphere earth(EARTH_RADIUS);
	float earthRotationAngle = 0;
	float earthOrbitAngle = 0;
	std::deque<Vector3> earthPath;

	sphere moon(MOON_RADIUS);
	float moonRotationAngle = 0;
	float moonOrbitAngle = 0;
	std::deque<Vector3> moonPath;

	sphere mercury(MERCURY_RADIUS);
	float mercuryRotationAngle = 0;
	float mercuryOrbitAngle = 0;
	std::deque<Vector3> mercuryPath;

	sphere venus(VENUS_RADIUS);
	float venusRotationAngle = 0;
	float venusOrbitAngle = 0;
	std::deque<Vector3> venusPath;

	sphere mars(MARS_RADIUS);
	float marsRotationAngle = 0;
	float marsOrbitAngle = 0;
	std::deque<Vector3> marsPath;

	sphere jupiter(JUPITER_RADIUS);
	float jupiterRotationAngle = 0;
	float jupiterOrbitAngle = 0;
	std::deque<Vector3> jupiterPath;

	sphere saturn(SATURN_RADIUS);
	float saturnRotationAngle = 0;
	float saturnOrbitAngle = 0;
	std::deque<Vector3> saturnPath;

	sphere uranus(URANUS_RADIUS);
	float uranusRotationAngle = 0;
	float uranusOrbitAngle = 0;
	std::deque<Vector3> uranusPath;

	sphere neptune(NEPTUNE_RADIUS);
	float neptuneRotationAngle = 0;
	float neptuneOrbitAngle = 0;
	std::deque<Vector3> neptunePath;
	#pragma endregion

	Camera3D cam3D;
	cam3D.position = {900, 900, 900};
	cam3D.projection = CAMERA_PERSPECTIVE;
	cam3D.fovy = 45.0f;
	cam3D.up = {0, 1, 0};
	localCam3DStats camStats;


	// main loop
	while (!WindowShouldClose())
	{
		#pragma region updates
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

		// info for debug overlay and orbit paths
		sun.setPosition(cos(sunRotationAngle), sin(sunRotationAngle));

		float mercuryDist = SUN_MERCURY_DISTANCE + sun.getRadius() + mercury.getRadius();
		mercury.setPosition(mercuryDist * cos(mercuryOrbitAngle), mercuryDist * sin(mercuryOrbitAngle));

		float venusDist = SUN_VENUS_DISTANCE + sun.getRadius() + venus.getRadius();
		venus.setPosition(venusDist * cos(venusOrbitAngle), venusDist * sin(venusOrbitAngle));

		float earthDist = SUN_EARTH_DISTANCE + sun.getRadius() + earth.getRadius();
		earth.setPosition(earthDist * cos(earthOrbitAngle), earthDist * sin(earthOrbitAngle));

		float moonDist = 0; // TODO fix this to be correct
		moon.setPosition(moonDist * cos(moonOrbitAngle), moonDist * sin(moonOrbitAngle));

		float marsDist = SUN_MARS_DISTANCE + sun.getRadius() + mars.getRadius();
		mars.setPosition(marsDist * cos(marsOrbitAngle), marsDist * sin(marsOrbitAngle));

		float jupiterDist = SUN_JUPITER_DISTANCE + sun.getRadius() + jupiter.getRadius();
		jupiter.setPosition(jupiterDist * cos(jupiterOrbitAngle), jupiterDist * sin(jupiterOrbitAngle));

		float saturnDist = SUN_SATURN_DISTANCE + sun.getRadius() + saturn.getRadius();
		saturn.setPosition(saturnDist * cos(saturnOrbitAngle), saturnDist * sin(saturnOrbitAngle));

		float uranusDist = SUN_URANUS_DISTANCE + sun.getRadius() + uranus.getRadius();
		uranus.setPosition(uranusDist * cos(uranusOrbitAngle), uranusDist * sin(uranusOrbitAngle));

		float neptuneDist = SUN_NEPTUNE_DISTANCE + sun.getRadius() + neptune.getRadius();
		neptune.setPosition(neptuneDist * cos(neptuneOrbitAngle), neptuneDist * sin(neptuneOrbitAngle));

		// update orbit paths for bodies, to be drawn later
		mercuryPath.push_back(mercury.getPosition());
		venusPath.push_back(venus.getPosition());
		earthPath.push_back(earth.getPosition());
		moonPath.push_back(moon.getPosition());
		marsPath.push_back(mars.getPosition());
		jupiterPath.push_back(jupiter.getPosition());
		saturnPath.push_back(saturn.getPosition());
		uranusPath.push_back(uranus.getPosition());
		neptunePath.push_back(neptune.getPosition());

		// remove excess from dequeues
		if (mercuryPath.size() >= ORBIT_PATH_SIZE)
			mercuryPath.pop_back();
		if (venusPath.size() >= ORBIT_PATH_SIZE)
			venusPath.pop_back();
		if (earthPath.size() >= ORBIT_PATH_SIZE)
			earthPath.pop_back();
		if (moonPath.size() >= ORBIT_PATH_SIZE)
			moonPath.pop_back();
		if (marsPath.size() >= ORBIT_PATH_SIZE)
			marsPath.pop_back();
		if (jupiterPath.size() >= ORBIT_PATH_SIZE)
			jupiterPath.pop_back();
		if (saturnPath.size() >= ORBIT_PATH_SIZE)
			saturnPath.pop_back();
		if (uranusPath.size() >= ORBIT_PATH_SIZE)
			uranusPath.pop_back();
		if (neptunePath.size() >= ORBIT_PATH_SIZE)
			neptunePath.pop_back();
		#pragma endregion

		BeginDrawing();
		ClearBackground(BLACK);

		BeginMode3D(cam3D);

		//DrawGrid(5000, 500);

		#pragma region inputs
		// mouse

		// left click
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			Vector2 mouseDelta = GetMouseDelta();
			std::cout << "mouse delta x: " << mouseDelta.x << ", mouse delta y: " << mouseDelta.y << std::endl;

			if (mouseDelta.x > 0)
			{
				camStats.orientation.x += MOUSE_SENSITIVITY;
			}
			else if (mouseDelta.x < 0)
			{
				camStats.orientation.x -= MOUSE_SENSITIVITY;
			}
			else if (mouseDelta.x == 0)
			{
				camStats.orientation.x = 0;
			}

			if (mouseDelta.y > 0)
			{
				camStats.orientation.y += MOUSE_SENSITIVITY;
			}
			else if (mouseDelta.y < 0)
			{
				camStats.orientation.y -= MOUSE_SENSITIVITY;
			}
			else if (mouseDelta.y == 0)
			{
				camStats.orientation.y = 0;
			}
		}
		else
		{
			camStats.orientation.x = 0;
			camStats.orientation.y = 0;
			camStats.orientation.z = 0;
		}

		// right click
		if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && !debugOverlay)
		{
			debugOverlay = true;
			std::cout << "right click" << std::endl;
		}
		else if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && debugOverlay)
		{
			debugOverlay = false;
			std::cout << "right click" << std::endl;
		}

		// mouse wheel
		if (GetMouseWheelMoveV().y != 0)
		{
			std::cout << "wheel y: " << GetMouseWheelMoveV().y << std::endl;
			mouseWheelMod += GetMouseWheelMoveV().y * SPEED_MODIFIER;
			std::cout << "wheelmod: " << mouseWheelMod << std::endl;
		}

		// keys
		if (IsKeyDown(KEY_W))
		{
			camStats.movement = {CAMERA_MOVE_SPEED * mouseWheelMod, 0, 0};
			std::cout << "W pressed" << std::endl;
		}
		else if (IsKeyDown(KEY_A))
		{
			camStats.movement = {0, -(CAMERA_MOVE_SPEED * mouseWheelMod), 0};
			std::cout << "A pressed" << std::endl;
		}
		else if (IsKeyDown(KEY_S))
		{
			camStats.movement = {-(CAMERA_MOVE_SPEED * mouseWheelMod), 0, 0};
			std::cout << "S pressed" << std::endl;
		}
		else if (IsKeyDown(KEY_D))
		{
			camStats.movement = {0, CAMERA_MOVE_SPEED * mouseWheelMod, 0};
			std::cout << "D pressed" << std::endl;
		}
		else if (IsKeyDown(KEY_SPACE))
		{
			camStats.movement = {0, 0, CAMERA_MOVE_SPEED * mouseWheelMod};
			std::cout << "space pressed" << std::endl;
		}
		else if (IsKeyDown(KEY_LEFT_SHIFT))
		{
			camStats.movement = {0, 0, -(CAMERA_MOVE_SPEED * mouseWheelMod)};
			std::cout << "left shift pressed" << std::endl;
		}
		else
		{
			camStats.movement = {0, 0, 0};
		}

		UpdateCameraPro(&cam3D, camStats.movement, camStats.orientation, 0);
		#pragma endregion

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
				DrawPoint3D({0, 0, 0}, WHITE);
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


		#pragma region orbitPaths
		for (int i = 0; i < mercuryPath.size(); i++)
		{
			DrawSphere(mercuryPath[i], ORBIT_PATH_THICKNESS, DARKGREEN);
		}
		for (int i = 0; i < venusPath.size(); i++)
		{
			DrawSphere(venusPath[i], ORBIT_PATH_THICKNESS, YELLOW);
		}
		for (int i = 0; i < earthPath.size(); i++)
		{
			DrawSphere(earthPath[i], ORBIT_PATH_THICKNESS, BLUE);
		}
		// TODO add moon
		for (int i = 0; i < marsPath.size(); i++)
		{
			DrawSphere(marsPath[i], ORBIT_PATH_THICKNESS, RED);
		}
		for (int i = 0; i < jupiterPath.size(); i++)
		{
			DrawSphere(jupiterPath[i], ORBIT_PATH_THICKNESS, BEIGE);
		}
		for (int i = 0; i < saturnPath.size(); i++)
		{
			DrawSphere(saturnPath[i], ORBIT_PATH_THICKNESS, YELLOW);
		}
		for (int i = 0; i < uranusPath.size(); i++)
		{
			DrawSphere(uranusPath[i], ORBIT_PATH_THICKNESS, SKYBLUE);
		}
		for (int i = 0; i < neptunePath.size(); i++)
		{
			DrawSphere(neptunePath[i], ORBIT_PATH_THICKNESS, PURPLE);
		}
		#pragma endregion



		EndMode3D();

		if (debugOverlay) // TODO finish debug overlay on right click
		{
			DrawText(TextFormat("Mercury x: %f", mercury.getPosition().x), 50, 50, 30, RED);
		}

		EndDrawing();
	}


	CloseWindow();
}