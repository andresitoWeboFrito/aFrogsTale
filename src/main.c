#include "aFrogsTale.h"

int main()
{
	GameData game;

	int playerPos[2] = {0, 0};

	game.map = loadMap("maps/default.map");

	if (game.map)
	{
		size_t i = 0;
		while (game.map[i])
		{
			printf("%s", game.map[i]);
			i++;
		}
	}

	InitWindow(SCREEN_W, SCREEN_H, "test");
	game.sprites.wall = LoadTexture("sprites/wall.png");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		// 	// check for pressed keys
		// 	if (IsKeyPressed(KEY_D))
		// 		playerPos[0] += SPRITE_SIZE;
		// 	else if (IsKeyPressed(KEY_A))
		// 		playerPos[0] -= SPRITE_SIZE;
		// 	else if (IsKeyPressed(KEY_S))
		// 		playerPos[1] += SPRITE_SIZE;
		// 	else if (IsKeyPressed(KEY_W))
		// 		playerPos[1] -= SPRITE_SIZE;

		// draw each frame
		BeginDrawing();

		ClearBackground(RAYWHITE);
		renderMap(game.map, game.sprites);
		// 	DrawTexture(texture, playerPos[0], playerPos[1], WHITE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}