#include "aFrogsTale.h"

void initGame(GameData *game)
{
	game->map = loadMap("maps/default.map");

	parseMap(game);

	InitWindow(SCREEN_W, SCREEN_H, "test");
	game->sprites.wall = LoadTexture("sprites/wall.png");
	game->sprites.ground = LoadTexture("sprites/ground.png");
	game->sprites.player = LoadTexture("sprites/player.png");

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
		// TODO: I have to initialze the player position to the P of the map!
		renderPlayer(game.playerPos, game.sprites.player);

		EndDrawing();
	}
	CloseWindow();

	return 0;
}