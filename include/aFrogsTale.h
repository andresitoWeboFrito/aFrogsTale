// This going to be programmed using the raylib because apparently is of the easiest thing to do
#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// global consts
#define SPRITE_SIZE 64
#define SCREEN_W 800
#define SCREEN_H 450
#define MAX_COINS 100

typedef enum
{
	Left,
	Right
} Direction;

typedef struct
{
	size_t x;
	size_t y;
} Position;

typedef struct
{
	Position pos;
	bool collected;
} Coin;

typedef struct
{
	Coin coins[MAX_COINS];
	size_t nCoins;
} CoinsData;

typedef struct
{
	Texture2D playerRight;
	Texture2D playerLeft;
	Texture2D wall;
	Texture2D ground;
	Texture2D coin;
} Sprites;

typedef struct
{
	char **map;
	Position playerPos;
	Direction playerDirection;
	Sprites sprites;
	CoinsData coinsData;
} GameData;

/* Functions of map.c */

char **reallocMap(char **oldMap);
size_t countLines(char **map);
char **loadMap(const char *path);
char *formatLine(const char *buffer);
void parseMap(GameData *game);
bool checkMap(char **map);
bool checkWalls(char **map);
bool checkPlayer(char **map);
void addCoin(CoinsData *coinsData, Position pos);

/* Functions of render.c */
void renderBackground(char **map, Sprites sprites);
void renderPlayer(Position playerPos, Direction playerDirection, const Sprites *sprites);
void renderCoins(const CoinsData *coinsData, const Texture2D *coinSprite);

/* Functions of input.c */
void checkPressedKeys(GameData *game);
