#include "aFrogsTale.h"

/*
TODOS:
	- sync enemy with attack animation
	- add door info struct
	- add more animations (collecting coins, door opening, etc)
	- improve combat (more life points for enemies, different attacks, enemies attack back...)
	- make enemies move
	- add map generator
	- add the bump with an enemy animation (hard coded?)
	- improve walls and borders
	- add different ground textures
	- add sounds
	- add main title and ui?
	- make the animation Instances to be stored in dynamic memory (malloc). I think this is a must when i have multiple animations?
	- function to update all of the timers
	*/

bool initGame(GameData *game)
{
	game->map = loadMap(game->mapPath);
	if (!game->map)
	{
		return false;
	}

	game->player.lookDir = Right;
	game->player.lives = 3;
	game->player.animation.live = false;
	game->coinsData.nCoins = 0;
	game->enemiesData.nEnemies = 0;
	game->door.isOpen = false;
	game->state = Playing;
	game->score = 0;

	if (!checkMap(game->map))
		return false;

	parseMap(game);

	InitWindow(game->mapWidth * SPRITE_SIZE, (game->mapHeigth + 1.5) * SPRITE_SIZE, "aFrogsTale");
	if (!loadAllSpritesAndAnimations(&game->sprites, &game->animationsDataBase))
		return false;

	SetTargetFPS(GAME_SPEED);

	return true;
}

int main(int argc, char **argv)
{
	GameData game;
	float timer = 0;
	unsigned int frameCounter = 0;

	if (argc == 2)
	{
		game.mapPath = argv[1];
		printf("Loading the map from %s\n", game.mapPath);
	}
	else
	{
		game.mapPath = "maps/default.map";
		printf("No game map provided, loading the default one (at maps/default.map)\n");
	}

	if (!initGame(&game))
		return 0;
	while (!WindowShouldClose() && game.state == Playing)
	{
		// TODO: move the timer to the player struct
		timer = timer + GetFrameTime();
		updateTimers(&game.player, &game.enemiesData);

		// Check the player inputs
		checkPressedKeys(&game, &timer);

		// Actions of the enemies
		moveEnemies(&game);

		// draw each frame
		BeginDrawing();
		ClearBackground(BLACK);
		renderBackground(game.map, &game.sprites);
		renderExit(&game.door, &game.sprites.doorOpen, &game.sprites.doorClosed);

		renderPlayer(&game.player, &game.sprites);
		renderCoins(&game.coinsData, &game.sprites.coin);
		renderEnemies(&game.enemiesData, &game.sprites.enemy);
		renderCounters(&game);
		EndDrawing();

		// update the animation frames
		updateAnimations(&frameCounter, &game.coinsData, &game.player);
		// update the frame counter
		++frameCounter;
	}
	CloseWindow();

	if (game.state == Won)
		printf("%sYou Won!\n%s", TERM_GREEN, TERM_RESET);
	else
		// TODO: this has to be color coded, to be well displayed against the raylib logger. But which color?
		printf("%sYou didn't won, but hey you can always try again ;)\n", TERM_YELLOW);

	printf("%sYour score was: %lu\n", TERM_GREEN, game.score);
	return 0;
}
