#include "aFrogsTale.h"

void renderBackground(char **map, Sprites sprites)
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
			else
				DrawTexture(sprites.ground, x * SPRITE_SIZE, y * SPRITE_SIZE, WHITE);
		}
	}
}

void renderPlayer(Position playerPos, Direction playerDirection, const Sprites *sprites)
{
	// This will be more complex when I have some kind of player animations
	if (playerDirection == Right)
		DrawTexture(sprites->playerRight, playerPos.x * SPRITE_SIZE, playerPos.y * SPRITE_SIZE, WHITE);
	else
		DrawTexture(sprites->playerLeft, playerPos.x * SPRITE_SIZE, playerPos.y * SPRITE_SIZE, WHITE);
}

void renderCoins(const CoinsData *coinsData, const Texture2D *coinSprite)
{
	for (size_t i = 0; i < coinsData->nCoins; i++)
	{
		if (!coinsData->coins[i].collected)
		{
			DrawTexture(*coinSprite, coinsData->coins[i].pos.x * SPRITE_SIZE, coinsData->coins[i].pos.y * SPRITE_SIZE, WHITE);
		}
	}
}
