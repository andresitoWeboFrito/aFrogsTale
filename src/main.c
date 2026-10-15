#include "aFrogsTale.h"

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 450;
	int playerPos[2] = {0, 0};

	InitWindow(screenWidth, screenHeight, "test");
	Texture2D texture = LoadTexture("sprites/Player.png");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		// check for pressed keys
		if (IsKeyDown(KEY_D))
			playerPos[0] += 2;
		else if (IsKeyDown(KEY_A))
			playerPos[0] -= 2;
		else if (IsKeyDown(KEY_S))
			playerPos[1] += 2;
		else if (IsKeyDown(KEY_W))
			playerPos[1] -= 2;

		// draw each frame
		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawTexture(texture, playerPos[0], playerPos[1], WHITE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}