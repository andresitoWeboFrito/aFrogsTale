#include "aFrogsTale.h"

void updateAnimations(unsigned int *frameCounter, CoinsData *coins, Player *player)
{
	if (*frameCounter >= (GAME_SPEED / ANIMATION_SPEED))
	{
		updatePlayerAnimation(player);
		// to be added when i have other animations coins door, etc
		// updateEnemiesAnimations();
		updateOtherAnimations(coins);
		*frameCounter = 0;
	}
}

void updatePlayerAnimation(Player *player)
{
	if (player->animation)
	{
		if (player->animation->actualFrame < player->animation->data->nFrames) // should be nFrames -1 ?
			player->animation->actualFrame++;
		else
		{
			player->animation->actualFrame = 0;
			player->animation = NULL;
		}
	}
}

void updateOtherAnimations(CoinsData *coinsData)
{
	for (size_t i = 0; i < coinsData->nCoins; i++)
	{
		AnimationInstance *animation = coinsData->coins[i].currentAnimation;

		if (animation)
		{
			if (animation->actualFrame < animation->data->nFrames)
			{
				animation->actualFrame++;
			}
			else
			{
				animation->actualFrame = 0;
				animation->live = false; // TODO: remove the live flag?
				coinsData->coins[i].currentAnimation = NULL;
			}
		}
	}
}

AnimationInstance instantiateAnimation(const AnimationData *data)
{
	AnimationInstance instance;
	instance.data = data;
	instance.actualFrame = 0;
	instance.live = true; // TODO: Do I really need the live flag?

	return instance;
}
