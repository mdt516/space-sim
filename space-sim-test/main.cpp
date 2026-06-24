#include <raylib.h>


int main()
{
	InitWindow(1920, 1080, "test-window");

	while (!WindowShouldClose())
	{
		BeginDrawing();

		DrawCircle(0, 0, 20, RED);

		EndDrawing();
	}


	return 0;
}