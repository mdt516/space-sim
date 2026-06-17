#include <raylib.h>


const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const char* TITLE = "space-sim";

class sphere
{
public:
	sphere(int x, int y, int z, int r) : v(x, y, z), radius(r)
	{}

	Vector3 getVector() const { return v; }
	float getRadius() const { return radius; }

private:
	Vector3 v;
	float radius = 0;
};

int main()
{
	SetTargetFPS(60);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);

	sphere earth(40, 0, 40, 5);
	sphere sun(0, 0, 0, 20);
	sphere moon(45, 0, 45, 2);

	Camera3D cam;
	cam.position = {60, 60, 60};
	cam.projection = CAMERA_PERSPECTIVE;
	cam.fovy = 45.0f;
	cam.up = {0, 1, 0};

	cam.target = sun.getVector();

	// main loop
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		BeginMode3D(cam);
		
		UpdateCamera(&cam, CAMERA_FREE);

		DrawSphere(earth.getVector(), earth.getRadius(), BLUE);
		DrawSphere(sun.getVector(), sun.getRadius(), YELLOW);
		DrawSphere(moon.getVector(), moon.getRadius(), GRAY);

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			cam.target = sun.getVector();
		}

		EndMode3D();
		EndDrawing();
	}


	CloseWindow();
}