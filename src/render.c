#include "aFrogsTale.h"

void renderMap(char **map, Sprites sprites)
{
	// so this has to be a funtion that renders the map (i.e the background?)
	// so at the moment only walls and ground?
	// player can be painted on top I suppose

	for (size_t y = 0; y < countLines(map); y++)
	{
		for (size_t x = 0; x < strlen(map[y]); x++)
		{
			if (map[y][x] == '#')
				DrawTexture(sprites.wall, x * SPRITE_SIZE, y * SPRITE_SIZE, WHITE);

			// else if (map[y][x] == ' ')
			else
				DrawTexture(sprites.ground, x * SPRITE_SIZE, y * SPRITE_SIZE, WHITE);
		}
	}
}

void renderPlayer(Position playerPos, Texture2D playerSprite)
{
	// This will be more complex when I have some kind of player animations
	DrawTexture(playerSprite, playerPos.x * SPRITE_SIZE, playerPos.y * SPRITE_SIZE, WHITE);
}
