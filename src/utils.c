#include "aFrogsTale.h"

bool isPosEqual(Position pos1, Position pos2)
{
	return (pos1.x == pos2.x && pos1.y == pos2.y);
}

bool loadSprite(Texture2D *texture, const char *name)
{
	// Build the full path to the file
	char fullPath[256];
	fullPath[0] = '\0';
	strcat(fullPath, "sprites/");
	strncat(fullPath, name, sizeof(fullPath) - (sizeof(name) + 1));

	*texture = LoadTexture(fullPath);
	if (!IsTextureValid(*texture))
	{
		printf("%sUnable to load the %s sprite!\n%s", TERM_RED, name, TERM_RESET);
		return false;
	}
	return true;
}

bool loadAllSprites(Sprites *sprites)
{
	if (!loadSprite(&sprites->coin, "coin.png"))
		return false;
	else if (!loadSprite(&sprites->doorClosed, "door_closed.png"))
		return false;
	else if (!loadSprite(&sprites->doorOpen, "door_open.png"))
		return false;
	else if (!loadSprite(&sprites->enemy, "enemy.png"))
		return false;
	else if (!loadSprite(&sprites->ground, "ground.png"))
		return false;
	else if (!loadSprite(&sprites->playerLeft, "player_left.png"))
		return false;
	else if (!loadSprite(&sprites->playerRight, "player_right.png"))
		return false;
	else if (!loadSprite(&sprites->wall, "wall.png"))
		return false;
	else
		return true;
}

Position calcNewPosition(Position oldPos, Direction direction)
{
	Position newPos;
	if (direction == Left)
	{
		newPos.x = oldPos.x - 1;
		newPos.y = oldPos.y;
	}
	else if (direction == Right)
	{
		newPos.x = oldPos.x + 1;
		newPos.y = oldPos.y;
	}
	else if (direction == Up)
	{
		newPos.x = oldPos.x;
		newPos.y = oldPos.y - 1;
	}
	else // direction == Down
	{
		newPos.x = oldPos.x;
		newPos.y = oldPos.y + 1;
	}
	return newPos;
}