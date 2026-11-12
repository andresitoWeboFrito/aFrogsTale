#include "aFrogsTale.h"

// TODO: fix animations!
// void bumpIntoEnemy(const Player *player, Position enemyPosition, const Sprites *sprites)
// {
// 	TODO: it feels off to have so much repeated code
// 	if (player->pos.x == enemyPosition.x)
// 	{
// 		bump on the X axis
// 		int distance = (enemyPosition.x - player->pos.x) * SPRITE_SIZE / 2;
// 		for (size_t i = 0; i < distance; i = i + 4)
// 		{
// 			if (player->lookDir == Right)
// 			{
// 				DrawTexture(sprites->playerRight, (player->pos.x * SPRITE_SIZE + i), player->pos.y * SPRITE_SIZE, WHITE);
// 			}
// 			else
// 			{
// 				DrawTexture(sprites->playerLeft, (player->pos.x * SPRITE_SIZE + i), player->pos.y * SPRITE_SIZE, WHITE);
// 			}
// 			sleep(1); // TODO: this has to bee less time
// 		}
// 	}
// 	else
// 	{
// 		bump on the Y axis
// 		int distance = (enemyPosition.y - player->pos.y) * SPRITE_SIZE;
// 		for (size_t i = 0; i < distance; i = i + 4)
// 		{
// 			if (player->lookDir == Right)
// 			{
// 				DrawTexture(sprites->playerRight, player->pos.x * SPRITE_SIZE, (player->pos.y * SPRITE_SIZE + i), WHITE);
// 			}
// 			else
// 			{
// 				DrawTexture(sprites->playerLeft, player->pos.x * SPRITE_SIZE, (player->pos.y * SPRITE_SIZE + i), WHITE);
// 			}
// 			sleep(1); // TODO: this has to be less time
// 		}
// 	}
// }

/*
anims:
- 1 the one atached to the player should update. What happens when gets changed and it is not finished? can this happen?
- 2 the one attachd for each enemy should also update
- 3 animations for objects, like coint etc should also update
-4 i dont like having to mark the player animations as live
*/
void updateAnimations(unsigned int *frameCounter, Animation *animations, Player *player, float *testTimer)
{
	if (*frameCounter >= (GAME_SPEED / ANIMATION_SPEED))
	{
		printf("Time since last frame: %f ms\n", (*testTimer * 1000));
		*testTimer = 0;
		updatePlayerAnimation(player);
		// updateEnemiesAnimations(); // TODO:
		// updateOtherAnimations();
		*frameCounter = 0;
	}
}

void updatePlayerAnimation(Player *player)
{
	if (player->animation)
	{
		if (player->animation->actualFrame < player->animation->nFrames) // should be nFrames -1 ?
			player->animation->actualFrame++;
		else
		{
			player->animation->actualFrame = 0;
			player->animation = NULL;
		}
	}
}
void updateOtherAnimations()
{
	// // TODO: the idea to no skip animations by the player / enemies is to dont use the live flag on those
	// for (size_t i = 0; i < N_ANIMATIONS; i++)
	// {
	// 	// TODO: this updates all the animations, maybe I should onyl update the ones I'm using?
	// 	if (animations[i].live)
	// 	{
	// 		if (animations[i].actualFrame < animations[i].nFrames)
	// 		{
	// 			animations[i].actualFrame++;
	// 		}
	// 		else
	// 		{
	// 			animations[i].actualFrame = 0;
	// 			animations[i].live = false;
	// 			player->animation = NULL;
	// 		}
	// 	}
	// }
}
