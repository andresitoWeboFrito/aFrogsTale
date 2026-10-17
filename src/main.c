#include "aFrogsTale.h"

int main()
{

	int playerPos[2] = {0, 0};

	char **map = loadMap("maps/default.map");

	// TODO: fix this because only outputs rows of ######
	if (map)
	{
		size_t i = 0;
		while (map[i])
		{
			printf("%s", map[i]);
			i++;
		}
	}

	// InitWindow(SCREEN_W, SCREEN_H, "test");
	// Texture2D texture = LoadTexture("sprites/Player.png");

	// SetTargetFPS(60);

	// while (!WindowShouldClose())
	// {
	// 	// check for pressed keys
	// 	if (IsKeyPressed(KEY_D))
	// 		playerPos[0] += SPRITE_SIZE;
	// 	else if (IsKeyPressed(KEY_A))
	// 		playerPos[0] -= SPRITE_SIZE;
	// 	else if (IsKeyPressed(KEY_S))
	// 		playerPos[1] += SPRITE_SIZE;
	// 	else if (IsKeyPressed(KEY_W))
	// 		playerPos[1] -= SPRITE_SIZE;

	// 	// draw each frame
	// 	BeginDrawing();

	// 	ClearBackground(RAYWHITE);
	// 	DrawTexture(texture, playerPos[0], playerPos[1], WHITE);

	// 	EndDrawing();
	// }

	// CloseWindow();

	return 0;
}