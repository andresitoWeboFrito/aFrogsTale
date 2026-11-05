#include "aFrogsTale.h"

// TODO: change to be able to move instantly the first time
void checkPressedKeys(GameData *game, float *timer)
{
	// Movement keys (with a timer!)
	if (*timer >= MOVEMENT_TIMER)
	{
		if (IsKeyDown(KEY_D))
		{
			checkMovementCollisions(game, Right);
			game->player.lookDir = Right;
			*timer = 0;
		}
		else if (IsKeyDown(KEY_A))
		{
			checkMovementCollisions(game, Left);
			game->player.lookDir = Left;
			*timer = 0;
		}
		else if (IsKeyDown(KEY_S))
		{
			checkMovementCollisions(game, Down);
			*timer = 0;
		}
		else if (IsKeyDown(KEY_W))
		{
			checkMovementCollisions(game, Up);
			*timer = 0;
		}
	}

	// TODO: use another key to attack?
	if (IsKeyPressed(KEY_F))
		playerAttack(&game->player, &game->enemiesData, &game->sprites);
}