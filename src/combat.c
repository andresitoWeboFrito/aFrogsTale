#include "aFrogsTale.h"

// TODO: right now the direction will only be left or right
void playerAttack(Position playerPos, Direction playerDir, EnemiesData *enemiesData)
{
	// TODO: play attack animation

	// figure out if there is any enemy in the direction of attack
	Enemy *attackedEnemy = findAttackedEnemy(playerPos, playerDir, enemiesData);
	if (attackedEnemy)
	{
		printf("Attacking the enemy at pos{%lu, %lu}\n", attackedEnemy->pos.x, attackedEnemy->pos.y);
	}
	else
	{
		printf("No attacked enemy!\n");
	}
	// kill it as life is only one point
}
Enemy *findAttackedEnemy(Position playerPos, Direction attackDir, const EnemiesData *enemiesData)
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
