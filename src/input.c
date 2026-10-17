#include "aFrogsTale.h"

void checkPressedKeys(GameData *game)
{
	// i dont like the check against the wall, its a bit flinicky
	if (IsKeyPressed(KEY_D) && game->map[game->playerPos.y][game->playerPos.x + 1] != '#')
		++game->playerPos.x;
	else if (IsKeyPressed(KEY_A) && game->map[game->playerPos.y][game->playerPos.x - 1] != '#')
		--game->playerPos.x;
	else if (IsKeyPressed(KEY_S) && game->map[game->playerPos.y + 1][game->playerPos.x] != '#')
		++game->playerPos.y;
	else if (IsKeyPressed(KEY_W) && game->map[game->playerPos.y - 1][game->playerPos.x] != '#')
		--game->playerPos.y;
}