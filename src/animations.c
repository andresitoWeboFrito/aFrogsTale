#include "aFrogsTale.h"

// TODO: fix animations!
// TODO: the animations should not be blocking?
void bumpIntoEnemy(const Player *player, Position enemyPosition, const Sprites *sprites)
{
	// TODO: it feels off to have so much repeated code
	if (player->pos.x == enemyPosition.x)
	{
		// bump on the X axis
		int distance = (enemyPosition.x - player->pos.x) * SPRITE_SIZE / 2;
		for (size_t i = 0; i < distance; i = i + 4)
		{
			if (player->lookDir == Right)
			{
				DrawTexture(sprites->playerRight, (player->pos.x * SPRITE_SIZE + i), player->pos.y * SPRITE_SIZE, WHITE);
			}
			else
			{
				DrawTexture(sprites->playerLeft, (player->pos.x * SPRITE_SIZE + i), player->pos.y * SPRITE_SIZE, WHITE);
			}
			sleep(1); //TODO: this has to bee less time
		}
	}
	else
	{
		// bump on the Y axis
		int distance = (enemyPosition.y - player->pos.y) * SPRITE_SIZE;
		for (size_t i = 0; i < distance; i = i + 4)
		{
			if (player->lookDir == Right)
			{
				DrawTexture(sprites->playerRight, player->pos.x * SPRITE_SIZE, (player->pos.y * SPRITE_SIZE + i), WHITE);
			}
			else
			{
				DrawTexture(sprites->playerLeft, player->pos.x * SPRITE_SIZE, (player->pos.y * SPRITE_SIZE + i), WHITE);
			}
			sleep(1); //TODO: this has to be less time
		}
	}
}