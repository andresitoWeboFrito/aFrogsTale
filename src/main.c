#include "aFrogsTale.h"

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "test");
	Texture2D texture = LoadTexture("sprites/Player.png");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawTexture(texture, 0, 0, WHITE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}