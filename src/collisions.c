#include "aFrogsTale.h"

void checkCollisionWithCoins(CoinsData *coinsData, Position player, size_t *score)
{
	for (size_t i = 0; i < coinsData->nCoins; i++)
	{
		if (isPosEqual(coinsData->coins[i].pos, player) && !coinsData->coins[i].collected)
		{
			coinsData->coins[i].collected = true;
			coinsData->remaininCoins--;
			// TODO: give 10 points for coin?
			(*score)++;
			printf("Remaining Coins: %lu\n", coinsData->remaininCoins);
			return;
		}
	}
}

bool isCollidingWithEnemies(Position playerPos, const EnemiesData *enemiesData)
{
	for (size_t i = 0; i < enemiesData->nEnemies; i++)
	{
		const Enemy *enemy = &enemiesData->enemies[i];

		if (enemy->alive && isPosEqual(enemy->pos, playerPos))
		{
			return true;
		}
	}
	return false;
}

/**
 * This is should only be called on a new movement intention.
 * For things like if a enemy toches me, I have to do something different.
 */
void checkMovementCollisions(GameData *game, Direction playerDir)
{
	// calc new Pos
	Position newPos = calcNewPosition(game->player.pos, playerDir);

	// TODO: maybe dont block the player into colliding with an enemy. but dont let them ocuppy the same tile
	if (!(game->map[newPos.y][newPos.x] == '#') && !isCollidingWithEnemies(newPos, &game->enemiesData))
	{
		// If it is not wall or not a (live) enemy, update the position
		game->player.pos = newPos;
	}
	checkCollisionWithCoins(&game->coinsData, game->player.pos, &game->score);
	// check against door
	if (isPosEqual(game->player.pos, game->doorPos) && game->coinsData.remaininCoins == 0)
	{
		game->state = Won;
	}
}