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

void renderAnimation(Animation *animation, Position pos)
{
	// TODO: maybe put the rectangle with the Animation struct to not create it eeevery time
	// Create the rectangle to take out only one sprite from the sprite sheet
	Rectangle frameRectangle = {0.0f, 0.0f, (float)animation->spriteSheet.width / animation->nFrames, (float)animation->spriteSheet.height};

	// Move the rectangle to the current frame from the animation
	frameRectangle.x = SPRITE_SIZE * animation->actualFrame;

	Vector2 posVector = {.x = pos.x * SPRITE_SIZE, .y = pos.y * SPRITE_SIZE};
	DrawTextureRec(animation->spriteSheet, frameRectangle, posVector, WHITE);
}

void renderPlayer(Player *player, Sprites *sprites)
{
	if (player->animation)
	{
		renderAnimation(player->animation, player->pos);
	}
	else if (player->lookDir == Right)
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

void renderCounters(const GameData *game)
{
	DrawText(TextFormat("Score: %04d", game->score), ((game->mapWidth / 2 - 0.5) * SPRITE_SIZE), (game->mapHeigth + 0.25) * SPRITE_SIZE, 20, WHITE);
	DrawText(TextFormat("Lives %d", game->player.lives), (game->mapWidth / 2 * SPRITE_SIZE), (game->mapHeigth + 0.75) * SPRITE_SIZE, 20, WHITE);
}
