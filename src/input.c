#include "aFrogsTale.h"

void checkPressedKeys(GameData *game)
{
	if (IsKeyPressed(KEY_D))
	{
		checkMovementColisions(game, Right);
		game->playerLookDirection = Right;
	}
	else if (IsKeyPressed(KEY_A))
	{
		checkMovementColisions(game, Left);
		game->playerLookDirection = Left;
	}
	else if (IsKeyPressed(KEY_S))
		checkMovementColisions(game, Down);
	else if (IsKeyPressed(KEY_W))
		checkMovementColisions(game, Up);
}

/**
 * This is should only be called on a new movement intention.
 * For things like if a enemy toches me, I have to do something different.
 */
void checkMovementColisions(GameData *game, Direction playerDir)
{
	// calc new Pos
	Position newPos = calcNewPosition(game->playerPos, playerDir);

	// TODO: better way to do this? Can i colide with an enemy?
	if (!(game->map[newPos.y][newPos.x] == '#'))
	{
		// If it is not wall, update the position
		game->playerPos = newPos;
	}
	checkCoins(&game->coinsData, game->playerPos);
	// check against door
	if (isPosEqual(game->playerPos, game->exitPos) && game->coinsData.remaininCoins == 0)
	{
		game->state = Won;
	}
	// check against enemy? -> dmg? (maybe this is for a check to happen EVERY time slice)
}

Position calcNewPosition(Position oldPos, Direction direction)
{
	Position newPos;
	if (direction == Left)
	{
		newPos.x = oldPos.x - 1;
		newPos.y = oldPos.y;
	}
	else if (direction == Right)
	{
		newPos.x = oldPos.x + 1;
		newPos.y = oldPos.y;
	}
	else if (direction == Up)
	{
		newPos.x = oldPos.x;
		newPos.y = oldPos.y - 1;
	}
	else // direction == Down
	{
		newPos.x = oldPos.x;
		newPos.y = oldPos.y + 1;
	}
	return newPos;
}

void checkCoins(CoinsData *coinsData, Position player)
{
	for (size_t i = 0; i < coinsData->nCoins; i++)
	{
		if (isPosEqual(coinsData->coins[i].pos, player) && !coinsData->coins[i].collected)
		{
			coinsData->coins[i].collected = true;
			coinsData->remaininCoins--;
			printf("Remaining Coins: %lu\n", coinsData->remaininCoins);
			// TODO: give some points to the player?
			return;
		}
	}
}
