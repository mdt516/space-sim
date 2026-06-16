#include <raylib.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const char* TITLE = "space-sim";

struct sphere
{
public:
	sphere(int x, int y, int z, int r) : v(x, y, z), radius(r)
	{
	}

	Vector3 getVector() { return v; }
	float getRadius() { return radius; }

private:
	Vector3 v;
	float radius = 0;
};

int main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);

	sphere earth(40, 0, 40, 5);
	sphere sun(0, 0, 0, 20);
	sphere moon(45, 0, 45, 2);

	Camera3D cam;
	cam.position = {60, 60, 60};
	cam.projection = CAMERA_PERSPECTIVE;



	// main loop
	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);
	}
}