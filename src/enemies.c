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
void calcNewEnemyPos(Position playerPos, Enemy *enemy, GameData *game)
{
	Direction longDir;
	Direction shortDir;
	calcMovementDirections(playerPos, enemy->pos, &longDir, &shortDir);
	// store the new direction (only left or right because is where it looks to)
	if (longDir == Left || longDir == Right)
		enemy->dir = longDir;
	else
		enemy->dir = shortDir;

	Position newPos = calcNewPosition(enemy->pos, longDir);
	// Check the tile
	TileStatus tileStatus = checkTile(newPos, game);
	if (tileStatus.free)
	{
		enemy->pos = newPos;
	}
	else
	{
		// The desired tile is blocked, try with the shortes direction
		newPos = calcNewPosition(enemy->pos, shortDir);
		tileStatus = checkTile(newPos, game);
		if (tileStatus.free)
		{
			enemy->pos = newPos;
		}
		else
		{
			// The second option of tile is also blocked. Can't move the enemy
			return;
		}
	}
}

void moveEnemies(GameData *game)
{
	for (size_t i = 0; i < game->enemiesData.nEnemies; i++)
	{
		Enemy *enemy = &game->enemiesData.enemies[i];
		if (enemy->alive && enemy->movementTimer > ENEMY_MOVEMENT_TIMER)
		{
			// Check if the player is in "viewing distance"
			if (calcDistance(game->player.pos, enemy->pos) <= enemy->viewDistance)
			{
				calcNewEnemyPos(game->player.pos, enemy, game);
				enemy->movementTimer = 0;
			}
		}
	}
}

void attackPlayer()
{
}
