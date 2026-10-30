#include "aFrogsTale.h"

void renderBackground(char **map, const Sprites *sprites)
{
	// so this has to be a funtion that renders the map (i.e the background?)
	// so at the moment only walls and ground?
	// player can be painted on top I suppose

	for (size_t y = 0; y < countLines(map); y++)
	{
		for (size_t x = 0; x < strlen(map[y]); x++)
		{
			if (map[y][x] == '#')
				DrawTexture(sprites->wall, x * SPRITE_SIZE, y * SPRITE_SIZE, WHITE);
			else
				DrawTexture(sprites->ground, x * SPRITE_SIZE, y * SPRITE_SIZE, WHITE);
		}
	}
}
void renderPlayer(const Player *player, const Sprites *sprites)

{
	// This will be more complex when I have some kind of player animations
	if (player->lookDir == Right)
		DrawTexture(sprites->playerRight, player->pos.x * SPRITE_SIZE, player->pos.y * SPRITE_SIZE, WHITE);
	else
		DrawTexture(sprites->playerLeft, player->pos.x * SPRITE_SIZE, player->pos.y * SPRITE_SIZE, WHITE);
}

void renderCoins(const CoinsData *coinsData, const Texture2D *coinSprite)
{
	for (size_t i = 0; i < coinsData->nCoins; i++)
	{
		const Coin *coin = &coinsData->coins[i];
		if (!coin->collected)
		{
			DrawTexture(*coinSprite, coin->pos.x * SPRITE_SIZE, coin->pos.y * SPRITE_SIZE, WHITE);
		}
	}
}

void renderExit(const GameData *game)
{
	if (game->coinsData.remaininCoins == 0)
		DrawTexture(game->sprites.doorOpen, game->doorPos.x * SPRITE_SIZE, game->doorPos.y * SPRITE_SIZE, WHITE);
	else
		DrawTexture(game->sprites.doorClosed, game->doorPos.x * SPRITE_SIZE, game->doorPos.y * SPRITE_SIZE, WHITE);
}

void renderEnemies(const EnemiesData *enemiesData, const Texture2D *enemySprite)
{
	for (size_t i = 0; i < enemiesData->nEnemies; i++)
	{
		const Enemy *enemy = &enemiesData->enemies[i];

		if (enemy->alive)
		{
			// at the moment there is only one sprite to render, later I'll have to check also the direction
			DrawTexture(*enemySprite, enemy->pos.x * SPRITE_SIZE, enemy->pos.y * SPRITE_SIZE, WHITE);
		}
	}
}