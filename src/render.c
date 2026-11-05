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

// TODO: maybe move the current animation to be done outside of the function once the animation is done?
// or change the PlayerAnimation::none animation to be a null pointer to animation struct?
void renderAnimation(Animation *animation, Position pos)
{
	// TODO: maybe put the rectangle with the Animation struct to not create it eeevery time
	// Create the rectangle to take out only one sprite from the sprite sheet
	Rectangle frameRectangle = {0.0f, 0.0f, (float)animation->spriteSheet.width / animation->nFrames, (float)animation->spriteSheet.height};

	// Move the rectangle to the current frame from the animation
	frameRectangle.x = SPRITE_SIZE * animation->actualFrame;

	Vector2 posVector = {.x = pos.x * SPRITE_SIZE, .y = pos.y * SPRITE_SIZE};

	DrawTextureRec(animation->spriteSheet, frameRectangle, posVector, WHITE);
	if (animation->actualFrame < animation->nFrames)
	{
		animation->actualFrame++;
	}
	else
	{
		animation->actualFrame = 0;
	}
}

void renderPlayer(Player *player, Sprites *sprites)
{
	// TODO: do i need some kind of check to stay in the animation until it has finished?
	if (player->currentAnimation != None)
	{
		/*
		 * TODO: move the rendering of the animations to outside?
		 * Because all of them should be updated at the same time
		 */

		if (player->currentAnimation == BasicAttackRight)
		{
			renderAnimation(&sprites->playerAttackRight, player->pos);
		}
		else if (player->currentAnimation == BasicAttackLeft)
		{
			renderAnimation(&sprites->playerAttackLeft, player->pos);
		}
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

void updateAnimations(unsigned int *frameCounter, Sprites *sprites, Player *player)
{
	// FIXME: this is not 10 fps but 10 frames in which each frame runes a 60fps!
	if (frameCounter >= ANIMATION_SPEED)
	{
		// TODO: change the  animations to an array so I can iterate over?
		if (player->currentAnimation == BasicAttackRight)
		{
			if (sprites->playerAttackRight.actualFrame < sprites->playerAttackRight.nFrames)
			{
				sprites->playerAttackRight.actualFrame++;
			}
			else
			{
				sprites->playerAttackRight.actualFrame = 0;
				player->currentAnimation = None;
			}
		}
		else if (player->currentAnimation == BasicAttackLeft)
		{
			if (sprites->playerAttackLeft.actualFrame < sprites->playerAttackLeft.nFrames)
			{
				sprites->playerAttackLeft.actualFrame++;
			}
			else
			{
				sprites->playerAttackLeft.actualFrame = 0;
				player->currentAnimation = None;
			}
		}
		*frameCounter = 0;
	}
}