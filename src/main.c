#include "aFrogsTale.h"

bool initGame(GameData *game)
{
	game->map = loadMap("maps/default.map");
	game->playerDirection = Right;
	game->coinsData.nCoins = 0;
	if (!checkMap(game->map))
		return false;

	parseMap(game);

	InitWindow(SCREEN_W, SCREEN_H, "aFrogsTale");
	game->sprites.wall = LoadTexture("sprites/wall.png");
	game->sprites.ground = LoadTexture("sprites/ground.png");
	game->sprites.playerRight = LoadTexture("sprites/player_right.png");
	game->sprites.playerLeft = LoadTexture("sprites/player_left.png");
	game->sprites.coin = LoadTexture("sprites/coin.png");
	SetTargetFPS(60);

	return true;
}

int main()
{
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
		renderBackground(game.map, game.sprites);
		renderPlayer(game.playerPos, game.playerDirection, &game.sprites);
		renderCoins(&game.coinsData, &game.sprites.coin);
		EndDrawing();
	}
	CloseWindow();

	return 0;
}