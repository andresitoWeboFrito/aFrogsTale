#include "aFrogsTale.h"

/*
 Movement of the enemies:
 1. They should move slow (every x frames)
 2. They should move when the player is in rage of them ( when they "see" him)
 3. they should attack the player when on the adjacent tile, but no hop on the same tile as him
 4. only while alive
 5. they do each one needs a timer of the last time it moved
 6. all the timers should be updated as per slice
 -> so we are having classes in c. Great :)
*/

// TODO:  change this so the check tile only takes what it needs
Position calcNewEnemyPos(Position playerPos, Position enemyPos, GameData *game)
{
	// TODO: figure out if the player is in range

	// Calc distance to player
	int xDistance = playerPos.x - enemyPos.x;
	int yDistance = playerPos.y - enemyPos.y;
	Direction enemyDir = Left;

	// figure out the direction to take
	if (abs(xDistance) > abs(yDistance))
	{
		if (xDistance > 0)
			enemyDir = Right;
		else
			enemyDir = Left;
	}
	else
	{
		if (yDistance > 0)
			enemyDir = Down;
		else
			enemyDir = Up;
	}

	// Check the tile
	TileStatus tileStatus = checkTile(calcNewPosition(enemyPos, enemyDir), game);

	if (tileStatus.free)
	{
		return (calcNewPosition(enemyPos, enemyDir));
	}
	else
	{
		// the tile is not free. try with the other direction? if not dont move
		// TODO: try with the other direction
		return enemyPos;
	}
}

void moveEnemies(GameData *game)
{
	for (size_t i = 0; i < game->enemiesData.nEnemies; i++)
	{
		Enemy *enemy = &game->enemiesData.enemies[i];
		if (enemy->alive && enemy->movementTimer > ENEMY_MOVEMENT_TIMER)
		{
			enemy->pos = calcNewEnemyPos(game->player.pos, enemy->pos, game);
			enemy->movementTimer = 0;
		}
	}
}

void attackPlayer()
{
}
