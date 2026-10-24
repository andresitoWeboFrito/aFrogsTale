#include "aFrogsTale.h"

bool initGame(GameData *game)
{
	game->map = loadMap("maps/default.map");
	// TODO: add failed loading of map
	game->playerLookDirection = Right;
	game->coinsData.nCoins = 0;
	game->state = Playing;

	// TODO: add map didn't pass the checks
	if (!checkMap(game->map))
		return false;

	parseMap(game);

	InitWindow(game->mapWidth * SPRITE_SIZE, game->mapHeigth * SPRITE_SIZE, "aFrogsTale");
	game->sprites.wall = LoadTexture("sprites/wall.png");
	game->sprites.ground = LoadTexture("sprites/ground.png");
	game->sprites.playerRight = LoadTexture("sprites/player_right.png");
	game->sprites.playerLeft = LoadTexture("sprites/player_left.png");
	game->sprites.coin = LoadTexture("sprites/coin.png");
	// TODO: change once I've drawn the real exit
	game->sprites.exit = LoadTexture("sprites/wall.png");
	SetTargetFPS(60);

	return true;
}

int main()
{
	// TODO: add the posibility of input a different map with argv**

	GameData game;

	if (!initGame(&game))
		return 0;
	while (!WindowShouldClose())
	{
		// check for pressed keys
		checkPressedKeys(&game);

		// draw each frame
		BeginDrawing();
		ClearBackground(BLACK);
		renderBackground(game.map, &game.sprites);
		renderCoins(&game.coinsData, &game.sprites.coin);
		renderExit(game.exitPos, &game.sprites.exit);
		renderPlayer(game.playerPos, game.playerLookDirection, &game.sprites);
		EndDrawing();
	}
	CloseWindow();

	return 0;
}