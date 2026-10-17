#include "aFrogsTale.h"

void renderMap(char **map, Sprites sprites)
{
	// so this has to be a funtion that renders the map (i.e the background?)
	// so at the moment only walls and ground?
	// player can be painted on top I suppose

	for (size_t y = 0; y < countLines(map); y++)
	{
		// TODO: this inner loop maybe gives problems because the /n is being stored at some of the lines?
		for (size_t x = 0; x < strlen(map[y]); x++)
		{
			if (map[y][x] == '#')
				DrawTexture(sprites.wall, x * SPRITE_SIZE, y * SPRITE_SIZE, WHITE);
				}
	}
}
