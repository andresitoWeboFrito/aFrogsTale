// This going to be programmed using the raylib because apparently is of the easiest thing to do
#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// global consts
#define SPRITE_SIZE 64
#define SCREEN_W 800
#define SCREEN_H 450

typedef struct
{
	Texture2D player;
	Texture2D wall;
	Texture2D ground;
} Sprites;

typedef struct
{
	char **map;
	Sprites sprites;
} GameData;

/* Functions of map.c */

char **reallocMap(char **oldMap);
size_t countLines(char **map);
char **loadMap(char *path);
char *formatLine(const char *buffer);

/* Functions of render.c */
void renderMap(char **map, Sprites sprites);
