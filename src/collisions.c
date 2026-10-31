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

	if (isCollidingWithEnemies(newPos, &game->enemiesData))
	{
		printf("Bumping into enemy at pos {%lu, %lu}\n", newPos.x, newPos.y);
		// TODO: fix the animation
		bumpIntoEnemy(&game->player, newPos, &game->sprites);
		game->player.lives--;
		printf("%sPlayer took damage! Remaining Lives: %u%s\n", TERM_RED, game->player.lives, TERM_RESET);
		// TODO: i have to make sure that the lives are atleas 1 when doing lives-- because could happen that the value underflows
	}
	else if (!(game->map[newPos.y][newPos.x] == '#'))
	{
		// If it is not wall or not a (live) enemy, update the position
		game->player.pos = newPos;
	}
	// check if a coin is collected
	checkCollisionWithCoins(&game->coinsData, game->player.pos, &game->score);

	// Update the game status
	if (isPosEqual(game->player.pos, game->doorPos) && game->coinsData.remaininCoins == 0)
	{
		game->state = Won;
	}
	else if (game->player.lives == 0)
	{
		game->state = Died;
	}
}