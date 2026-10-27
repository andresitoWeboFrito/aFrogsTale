// This going to be programmed using the raylib because apparently is of the easiest thing to do
#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// global consts
#define SPRITE_SIZE 64
#define MAX_COINS 100
#define MAX_ENEMIES 100

// escape codes for printf
#define TERM_GREEN "\033[32m"
#define TERM_RED "\033[31m"
#define TERM_YELLOW "\033[33m"
#define TERM_RESET "\033[0m"

// enums
typedef enum
{
	Left,
	Right,
	Up,
	Down
} Direction;

typedef enum
{
	Playing,
	Won,
	Died
} GameState;

// structs
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
	size_t remaininCoins;
} CoinsData;

typedef struct
{
	Position pos;
	Direction dir;
	bool alive;
} Enemy;

typedef struct
{
	Enemy enemies[MAX_ENEMIES];
	size_t nEnemies;
} EnemiesData;

// TODO: create a struct with the info relevant to the door(open, pos, ...)
// TODO: create a struct with the info relevant to the player?
typedef struct
{
	Texture2D playerRight;
	Texture2D playerLeft;
	Texture2D wall;
	Texture2D ground;
	Texture2D coin;
	Texture2D doorClosed;
	Texture2D doorOpen;
	Texture2D enemy;
} Sprites;

typedef struct
{
	char **map;
	char *mapPath;
	size_t mapWidth;
	size_t mapHeigth;
	Position playerPos;
	Direction playerLookDirection;
	Position doorPos;
	GameState state;
	Sprites sprites;
	CoinsData coinsData;
	EnemiesData enemiesData;
	size_t score;
} GameData;

/* Functions of map.c */

char **reallocMap(char **oldMap);
size_t countLines(char **map);
char **loadMap(const char *path);
char *formatLine(const char *buffer);
void parseMap(GameData *game);
bool checkMap(char **map);
bool checkWalls(char **map);
bool checkItems(char **map);
void addCoin(CoinsData *coinsData, Position pos);

/* Functions of render.c */
void renderBackground(char **map, const Sprites *sprites);
void renderPlayer(Position playerPos, Direction playerLookDirection, const Sprites *sprites);
void renderCoins(const CoinsData *coinsData, const Texture2D *coinSprite);
void renderExit(const GameData *game);

/* Functions of input.c */
void checkPressedKeys(GameData *game);
Position calcNewPosition(Position oldPos, Direction direction);
void checkMovementColisions(GameData *game, Direction playerDir);
void checkCoins(CoinsData *coinsData, Position player, size_t *score);

/* Functions of utils.c */
bool isPosEqual(Position pos1, Position pos2);
bool loadSprite(Texture2D *texture, const char *name);
bool loadAllSprites(Sprites *sprites);
