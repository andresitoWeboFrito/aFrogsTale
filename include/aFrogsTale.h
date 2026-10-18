// This going to be programmed using the raylib because apparently is of the easiest thing to do
#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// global consts
#define SPRITE_SIZE 64
#define SCREEN_W 800
#define SCREEN_H 450

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
	Texture2D playerRight;
	Texture2D playerLeft;
	Texture2D wall;
	Texture2D ground;
} Sprites;

typedef struct
{
	char **map;
	Position playerPos;
	Direction playerDirection;
	Sprites sprites;
} GameData;

/* Functions of map.c */

char **reallocMap(char **oldMap);
size_t countLines(char **map);
char **loadMap(const char *path);
char *formatLine(const char *buffer);
void parseMap(GameData *game);

/* Functions of render.c */
void renderMap(char **map, Sprites sprites);
void renderPlayer(Position playerPos, Direction playerDirection, const Sprites *sprites);

/* Functions of input.c */
void checkPressedKeys(GameData *game);
