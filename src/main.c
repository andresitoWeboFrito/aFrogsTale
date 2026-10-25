#include "aFrogsTale.h"

bool initGame(GameData *game)
{
	game->map = loadMap(game->mapPath);
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

int main(int argc, char **argv)
{
	GameData game;

	if (argc == 2)
	{
		game.mapPath = argv[1];
		printf("Loading the map from %s\n", game.mapPath);
	}
	else
	{
		game.mapPath = "maps/default.map";
		printf("No game map provided, loading the default one (at maps/default.map)\n");
	}

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