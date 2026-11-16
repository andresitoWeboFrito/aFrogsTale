#include "aFrogsTale.h"

bool initGame(GameData *game)
{
	game->map = loadMap(game->mapPath);
	if (!game->map)
	{
		return false;
	}

	game->player.lookDir = Right;
	game->player.lives = 3;
	game->player.animation = NULL;
	game->coinsData.nCoins = 0;
	game->enemiesData.nEnemies = 0;
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
		// Check the player inputs
		timer = timer + GetFrameTime();
		checkPressedKeys(&game, &timer);

		// draw each frame
		BeginDrawing();
		ClearBackground(BLACK);
		renderBackground(game.map, &game.sprites);
		renderCoins(&game.coinsData, &game.sprites.coin);
		renderExit(&game);
		renderEnemies(&game.enemiesData, &game.sprites.enemy);
		renderPlayer(&game.player, &game.sprites);
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

/*
TODOS:
	- sync enemy with attack animation
	- add points for killing enemy
	- add door inf struct
	- add more animations (collecting coins, door opening, etc)
	- improve combat (more life poitns for enemies, different attacks, enemies attack back...)
	- make enemies move
	- add map generator
	- add the bump with an enemy animation (hard coded?)
	- improve walls and borders
	- add different ground textures
	- add sounds
	- add main title and ui?

	quiero cargar una vez los sprite sheets.
	Y ahora cada objeto tiene un puntero a una animacion, y esa un puntero al sprite sheet
	- Cargar texturas
	- Conversor de no se que a el puntero al sprite sheet. TODO:
	- Parsear mapa
	opcion a:
		- cargo la animacion pa el objeto cuando la tengo que usar
	opcion b:
		- cargo la animacion al principio y la disparo cuando la tengo que usar

		que es cargar la animacion? crear el struct con el numero de frames?
	cargar el struct solo me interesan el frame actual, y quizas si la animacion esta alive?
*/
