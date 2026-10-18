#include "aFrogsTale.h"

void initGame(GameData *game)
{
	game->map = loadMap("maps/default.map");
	game->playerDirection = Right;

	parseMap(game);

	InitWindow(SCREEN_W, SCREEN_H, "test");
	game->sprites.wall = LoadTexture("sprites/wall.png");
	game->sprites.ground = LoadTexture("sprites/ground.png");
	game->sprites.playerRight = LoadTexture("sprites/player_right.png");
	game->sprites.playerLeft = LoadTexture("sprites/player_left.png");

	SetTargetFPS(60);
}

int main()
{
	GameData game;

	initGame(&game);
	while (!WindowShouldClose())
	{
		// check for pressed keys
		checkPressedKeys(&game);

		// draw each frame
		BeginDrawing();

		ClearBackground(BLACK);
		renderMap(game.map, game.sprites);
		renderPlayer(game.playerPos, game.playerDirection, &game.sprites);

		EndDrawing();
	}
	CloseWindow();

	return 0;
}
