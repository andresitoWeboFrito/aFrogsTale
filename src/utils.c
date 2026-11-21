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

bool loadAnimation(AnimationData *animationData, const char *name, unsigned int nFrames)
{
	// Build the full path to the file
	char fullPath[256];
	fullPath[0] = '\0';
	strcat(fullPath, "sprites/");
	strncat(fullPath, name, sizeof(fullPath) - (sizeof(name) + 1));

	animationData->spriteSheet = LoadTexture(fullPath);
	if (!IsTextureValid(animationData->spriteSheet))
	{
		printf("%sUnable to load the %s sprite sheet!\n%s", TERM_RED, name, TERM_RESET);
		return false;
	}
	animationData->nFrames = nFrames;
	return true;
}

bool loadAllSpritesAndAnimations(Sprites *sprites, AnimationsDatabase *animations)
{
	// Sprites
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

	// Animations
	else if (!loadAnimation(&animations->BasicPlayerAttackRight, "player_attack_right.png", 4))
		return false;
	else if (!loadAnimation(&animations->BasicPlayerAttackLeft, "player_attack_left.png", 4))
		return false;
	else if (!loadAnimation(&animations->CollectCoin, "collect_coin.png", 4))
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

// TODO: change to use the required data instead of the whole game
TileStatus checkTile(Position desiredTile, GameData *game)
{
	for (size_t i = 0; i < game->enemiesData.nEnemies; i++)
	{
		Enemy *enemy = &game->enemiesData.enemies[i];
		if (enemy->alive && isPosEqual(enemy->pos, desiredTile))
		{
			// there is an enemy on the desired tile
			return (TileStatus){.free = false, .item = EnemyEntity, .itemPtr = enemy};
		}
	}
	if (isPosEqual(desiredTile, game->player.pos))
	{
		// the player is on the tile
		return (TileStatus){.free = false, .item = PlayerEntity, .itemPtr = &game->player};
	}
	else if (game->map[desiredTile.y][desiredTile.x] == '#')
	{
		// there is a wall on the tile
		return (TileStatus){.free = false, .item = WallEntity, .itemPtr = NULL};
	}
	else
	{
		for (size_t i = 0; i < game->coinsData.nCoins; i++)
		{
			Coin *coin = &game->coinsData.coins[i];
			if (!coin->collected && isPosEqual(desiredTile, coin->pos))
			{
				return (TileStatus){.free = true, .item = CoinEntity, .itemPtr = coin};
			}
		}

		// if nothing, then we have an empty tile
		return (TileStatus){.free = true, .item = None, .itemPtr = NULL};
	}
}