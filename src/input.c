#include "aFrogsTale.h"

void checkPressedKeys(GameData *game)
{
	if (IsKeyPressed(KEY_D))
	{
		checkMovementCollisions(game, Right);
		game->player.lookDir = Right;
	}
	else if (IsKeyPressed(KEY_A))
	{
		checkMovementCollisions(game, Left);
		game->player.lookDir = Left;
	}
	else if (IsKeyPressed(KEY_S))
		checkMovementCollisions(game, Down);
	else if (IsKeyPressed(KEY_W))
		checkMovementCollisions(game, Up);
	// TODO: use another key to attack
	else if (IsKeyPressed(KEY_F))
		playerAttack(&game->player, &game->enemiesData);
}
