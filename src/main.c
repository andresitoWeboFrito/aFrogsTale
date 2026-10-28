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
	game->score = 0;

	if (!checkMap(game->map))
		return false;

	parseMap(game);

	InitWindow(game->mapWidth * SPRITE_SIZE, game->mapHeigth * SPRITE_SIZE, "aFrogsTale");
	if (!loadAllSprites(&game->sprites))
		return false;
	SetTargetFPS(60);

	return true;
}
// TODO: enemies and combat!!
// TODO: Score counter!

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
		renderEnemies(&game.enemiesData, &game.sprites.enemy);
		renderPlayer(game.playerPos, game.playerLookDirection, &game.sprites);
		EndDrawing();
	}
	CloseWindow();

	if (game.state == Won)
		printf("%sYou Won!\n%s", TERM_GREEN, TERM_RESET);
	else
		// TODO: this has to be color coded, to be well displayed against the raylib logger. But which color?
		printf("%sYou didn't won, but hey you can always try again ;)\n", TERM_YELLOW);

	printf("%sYour score was: %lu\n", TERM_GREEN, game.score);
	return 0;
}