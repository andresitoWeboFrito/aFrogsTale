#include "aFrogsTale.h"

// TODO: right now the attack direction will only be left or right
void playerAttack(Player *player, EnemiesData *enemiesData, const AnimationsDatabase *animationDB, size_t * score)
{
	if (player->lookDir == Right)
	{
		player->animation = instantiateAnimation(&animationDB->BasicPlayerAttackRight);
	}
	else
	{
		player->animation = instantiateAnimation(&animationDB->BasicPlayerAttackLeft);
	}

	// figure out if there is any enemy in the direction of attack
	Enemy *attackedEnemy = findAttackedEnemy(player->pos, player->lookDir, enemiesData);
	if (attackedEnemy)
	{
		printf("Attacking the enemy at pos{%lu, %lu}\n", attackedEnemy->pos.x, attackedEnemy->pos.y);
		attackedEnemy->alive = false;
		*score = *score + 100;
		// TODO: sync killing the enemy with the attack animation as of now is poping out before we even attack it.
	}
	else
	{
		printf("No attacked enemy!\n");
	}
	// kill it as life is only one point
}
Enemy *findAttackedEnemy(Position playerPos, Direction attackDir, EnemiesData *enemiesData)
{
	Enemy *attackedEnemy = NULL;
	// since the attack is to the next tile to it, the tile in wich the attack lands is calculated the same as when the player moves in one direction
	Position attackedTile = calcNewPosition(playerPos, attackDir);
	for (size_t i = 0; i < enemiesData->nEnemies; i++)
	{
		Enemy *enemy = &enemiesData->enemies[i];
		if (isPosEqual(enemy->pos, attackedTile) && enemy->alive)
		{
			attackedEnemy = enemy;
			return attackedEnemy;
		}
	}

	return attackedEnemy;
}