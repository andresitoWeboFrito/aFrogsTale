#include "aFrogsTale.h"

bool initGame(GameData *game)
{
	game->map = loadMap("maps/default.map");
	if (!game->map)
	{
		return false;
	}

	game->playerLookDirection = Right;
	game->coinsData.nCoins = 0;
	game->state = Playing;

	if (!checkMap(game->map))
		return false;

	parseMap(game);

	InitWindow(game->mapWidth * SPRITE_SIZE, game->mapHeigth * SPRITE_SIZE, "aFrogsTale");
	if (!loadAllSprites(&game->sprites))
		return false;
	SetTargetFPS(60);

	return true;
}

int main()
{
	// TODO: add the posibility of input a different map with argv**

	GameData game;

	if (!initGame(&game))
		return 0;
	while (!WindowShouldClose() && game.state == Playing)
	{
		// check for pressed keys
		checkPressedKeys(&game);

		// draw each frame
		BeginDrawing();
		ClearBackground(BLACK);
		renderBackground(game.map, &game.sprites);
		renderCoins(&game.coinsData, &game.sprites.coin);
		renderExit(&game);
		renderPlayer(game.playerPos, game.playerLookDirection, &game.sprites);
		EndDrawing();
	}
	CloseWindow();

	if (game.state == Won)
		printf("%sYou Won!\n", TERM_GREEN);
	else
		printf("%sYou didn't won, but hey you can always try again ;)\n", TERM_RED);

	// TODO: print score once its clear what it should be
	return 0;
}