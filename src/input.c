#include "aFrogsTale.h"

void checkPressedKeys(GameData *game)
{
	// i dont like the check against the wall, its a bit flinicky
	if (IsKeyPressed(KEY_D) && game->map[game->playerPos.y][game->playerPos.x + 1] != '#')
	{
		++game->playerPos.x;
		game->playerDirection = Right;
	}
	else if (IsKeyPressed(KEY_A) && game->map[game->playerPos.y][game->playerPos.x - 1] != '#')
	{
		--game->playerPos.x;
		game->playerDirection = Left;
	}
	else if (IsKeyPressed(KEY_S) && game->map[game->playerPos.y + 1][game->playerPos.x] != '#')
		++game->playerPos.y;
	else if (IsKeyPressed(KEY_W) && game->map[game->playerPos.y - 1][game->playerPos.x] != '#')
		--game->playerPos.y;
}

void checkCoins(CoinsData *coinsData, Position player)
{
	for (size_t i = 0; i < coinsData->nCoins; i++)
	{
		if ((coinsData->coins[i].pos.x == player.x) && (coinsData->coins[i].pos.y == player.y))
		{
			coinsData->coins[i].collected = true;
			// TODO: give some points to the player?
			return;
		}
	}
}