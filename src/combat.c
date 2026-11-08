#include "aFrogsTale.h"

// TODO: right now the attack direction will only be left or right
void playerAttack(Player *player, EnemiesData *enemiesData, Sprites *sprites)
{
	// TODO: this feels off, to have 2 variables that do the same thing
	if (player->lookDir == Right)
	{
		// TODO: have a function that gets the AnimationPointer from the animations enum? Also like a map
		player->animation = &sprites->animations[0];
		sprites->animations[0].live = true;
	}
	else
	{
		player->animation = &sprites->animations[1];
		sprites->animations[1].live = true;
	}

	// figure out if there is any enemy in the direction of attack
	Enemy *attackedEnemy = findAttackedEnemy(player->pos, player->lookDir, enemiesData);
	if (attackedEnemy)
	{
		printf("Attacking the enemy at pos{%lu, %lu}\n", attackedEnemy->pos.x, attackedEnemy->pos.y);
		attackedEnemy->alive = false;
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