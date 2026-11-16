// This going to be programmed using the raylib because apparently is of the easiest thing to do
#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// global consts
#define SPRITE_SIZE 64
#define MAX_COINS 100 // TODO: all of these should use dinamyc memory instead?
#define MAX_ENEMIES 100
#define MAX_ANIMATIONS 100
#define MOVEMENT_TIMER 0.2f
#define GAME_SPEED 60
#define ANIMATION_SPEED 12

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

typedef enum
{
	PlayerBasicAttackRight,
	PlayerBasicAttackLeft,
	CoinCollected
} AnimationName;

// structs
typedef struct
{
	size_t x;
	size_t y;
} Position;

typedef struct
{
	Texture2D spriteSheet;
	unsigned int nFrames;
} AnimationData;

typedef struct
{
	const AnimationData *data;
	unsigned int actualFrame;
	bool live;
} AnimationInstance;

typedef struct
{
	AnimationData BasicPlayerAttackLeft;
	AnimationData BasicPlayerAttackRight;
	AnimationData CollectCoin;
} AnimationsDatabase;

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
	Position pos;
	AnimationInstance currentAnimation;
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

typedef struct
{
	Position pos;
	Direction lookDir;
	unsigned int lives;
	AnimationInstance animation;
} Player;

typedef struct
{
	char **map;
	char *mapPath;
	size_t mapWidth;
	size_t mapHeigth;
	Player player;
	Position doorPos;
	GameState state;
	Sprites sprites;
	AnimationsDatabase animationsDataBase;
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
void addEnemy(EnemiesData *enemiesData, Position pos);

/* Functions of render.c */
void renderBackground(char **map, const Sprites *sprites);
void renderPlayer(Player *player, Sprites *sprites);
void renderCoins(const CoinsData *coinsData, const Texture2D *coinSprite);
void renderExit(const GameData *game);
void renderEnemies(const EnemiesData *enemiesData, const Texture2D *enemySprite);
void renderAnimation(AnimationInstance *animation, Position pos);
void renderCounters(const GameData *game);

/* Functions of input.c */
void checkPressedKeys(GameData *game, float *timer);

/* Functions of utils.c */
bool isPosEqual(Position pos1, Position pos2);
bool loadSprite(Texture2D *texture, const char *name);
bool loadAnimation(AnimationData *animationData, const char *name, unsigned int nFrames);
bool loadAllSpritesAndAnimations(Sprites *sprites, AnimationsDatabase *animations);
Position calcNewPosition(Position oldPos, Direction direction);

/* Functions of combat.c */
void playerAttack(Player *player, EnemiesData *enemiesData, const AnimationsDatabase *animationDB);
Enemy *findAttackedEnemy(Position playerPos, Direction attackDir, EnemiesData *enemiesData);

/* Functions of collisions.c */
void checkCollisionWithCoins(CoinsData *coinsData, Position player, size_t *score, const AnimationsDatabase *animationsDatabase);
bool isCollidingWithEnemies(Position playerPos, const EnemiesData *enemiesData);
void checkMovementCollisions(GameData *game, Direction playerDir);

/* Functions of animations.c */
// void bumpIntoEnemy(const Player *player, Position enemyPosition, const Sprites *sprites);
void updatePlayerAnimation(Player *player);
void updateAnimations(unsigned int *frameCounter, CoinsData *coins, Player *player);
void updateOtherAnimations(CoinsData *coinsData);
AnimationInstance instantiateAnimation(const AnimationData *data);
