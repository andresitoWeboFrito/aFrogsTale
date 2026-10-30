#include "aFrogsTale.h"

// load a map from memory
char **loadMap(const char *path)
{
	FILE *mapFile = fopen(path, "r");
	// buffer of size 256 to read the lines of the map. Should be enough
	char buffer[256];
	char *line = NULL;
	char **map = NULL;
	int i = 0;

	if (mapFile == NULL)
	{
		printf("Couldn't open file. Don't forget to put the /map at the beggining of the path.\n");
		return (NULL);
	}

	while (fgets(buffer, sizeof(buffer), mapFile))
	{
		// make the map a line bigger
		map = reallocMap(map);
		if (!map)
		{
			printf("Couldn't realocate the map\n");
			return (NULL);
		}

		// Copy the content of the buffer into a line
		line = formatLine(buffer);
		if (!line)
			return NULL;

		// store the line in the map
		map[i] = line;
		map[i + 1] = NULL;
		i++;
	}

	fclose(mapFile);
	return map;
}
char **reallocMap(char **oldMap)
{
	char **newMap;
	size_t i = 0;
	size_t nLines = countLines(oldMap);

	newMap = (char **)malloc(sizeof(char *) * (nLines + 2));

	if (newMap == NULL)
	{
		printf("failed when calling malloc\n");
		return NULL;
	}

	if (oldMap != NULL)
	{
		while (oldMap[i])
		{
			newMap[i] = oldMap[i];
			++i;
		}
		free(oldMap);
	}
	return newMap;
}

size_t countLines(char **map)
{
	size_t i = 0;
	if (map)
	{
		while (map[i])
			++i;
	}
	return i;
}

char *formatLine(const char *buffer)
{
	char *line = NULL;
	size_t len = 0;

	while (buffer[len] && buffer[len] != '\n')
	{
		len++;
	}

	line = (char *)malloc((len + 1) * sizeof(char));
	if (!line)
	{
		printf("failed when calling malloc\n");
		return NULL;
	}
	strncpy(line, buffer, len);
	line[len] = '\0';
	return line;
}

void parseMap(GameData *game)
{
	size_t longestLine = 0;
	size_t lineLength;

	for (size_t y = 0; y < countLines(game->map); y++)
	{
		lineLength = strlen(game->map[y]);
		if (lineLength > longestLine)
			longestLine = lineLength;

		for (size_t x = 0; x < lineLength; x++)
		{
			if (game->map[y][x] == 'P')
			{
				game->player.pos = (Position){.x = x, .y = y};
			}
			else if (game->map[y][x] == 'C')
			{
				// add the coin to the array
				addCoin(&game->coinsData, (Position){.x = x, .y = y});
			}
			else if (game->map[y][x] == 'D')
			{
				// the exit door of the level
				game->doorPos.x = x;
				game->doorPos.y = y;
			}
			else if (game->map[y][x] == 'E')
			{
				// add an enemy to the array
				addEnemy(&game->enemiesData, (Position){.x = x, .y = y});
			}
		}
	}

	game->mapWidth = longestLine;
	game->mapHeigth = countLines(game->map);

	game->coinsData.remaininCoins = game->coinsData.nCoins;
}

void addCoin(CoinsData *coinsData, Position pos)
{
	if (coinsData && coinsData->nCoins + 1 < MAX_COINS)
	{
		// add a new coin
		coinsData->coins[coinsData->nCoins].pos = pos;
		coinsData->coins[coinsData->nCoins].collected = false;
		coinsData->nCoins++;
	}
	else
	{
		// null ptr or maximum number of coins reached
		if (coinsData->nCoins + 1 >= MAX_COINS)
			printf("Maximum number of coins reached!\n");
		// TODO: make program fail?
	}
}

void addEnemy(EnemiesData *enemiesData, Position pos)
{
	if (enemiesData && enemiesData->nEnemies + 1 < MAX_ENEMIES)
	{
		// add a new enemy
		enemiesData->enemies[enemiesData->nEnemies].alive = true;
		enemiesData->enemies[enemiesData->nEnemies].dir = Left;
		enemiesData->enemies[enemiesData->nEnemies].pos = pos;
		enemiesData->nEnemies++;
	}
	else
	{
		// null ptr or maximum number of coins reached
		if (enemiesData->nEnemies + 1 >= MAX_ENEMIES)
			printf("Maximum number of enemies reached!\n");
		// TODO: make program fail?
	}
}

bool checkMap(char **map)
{
	/**
	 * Valid map should be:
	 * 1. Surrounded by walls '#'
	 * 2. Contains 1 player 'P'
	 * 3. Contains atleast 1 coin 'C'
	 * 4. Contains 1 exit door 'D'
	 * 5. Can contain enemies 'E'
	 */

	if (!checkWalls(map))
	{
		printf("%sThe map is not completely closed!\n%s", TERM_RED, TERM_RESET);
		return false;
	}
	else if (!checkItems(map))
	{
		printf("%sThe map doesn't have the correct number of Coins 'C', Players 'P', and/or Exits 'E'\n%s", TERM_RED, TERM_RESET);
		return false;
	}
	else
		return true;
}

bool checkWalls(char **map)
{
	// TODO: there is missing checks for non rectangular maps, like:
	/**
	 * ####
	 * #  #### <- this small square should also be closed top AND bottom
	 * #     # <-
	 * ####### <-
	 */
	if (!map)
		return false;
	size_t i = 0;
	size_t nLines = countLines(map);

	// Check the first row
	while (map[0][i] == '#')
	{
		++i;
	}
	if (map[0][i] != '\0')
		return false;

	// check the columns
	for (size_t j = 0; j < nLines - 1; j++)
	{
		size_t lineLen = strlen(map[j]) - 1;
		if (map[j][0] != '#' || map[j][lineLen] != '#')
			return false;
	}

	// okay so a generic colum of the worst case would be something like
	/**
	 * (blank spaces) ########### (blank spaces)
	 *  (blank spaces)#         # (blank paces)
	 * ###############           #####
	 * #                             #
	 * #                         #####
	 * ##########################
	 * So:
	 * the main thing is to check the line length aparently if there is a difference in the lenghts, there has to be an openeing / closing
	 * as of now checks a full line on the top and bottom and its missing a full line when the line gets bigger
	 *
	 */

	// Check the last row
	i = 0;
	while (map[nLines - 1][i] == '#')
	{
		++i;
	}
	if (map[nLines - 1][i] != '\0')
		return false;

	return true;
}

bool checkItems(char **map)
{
	unsigned int playerCounter = 0;
	unsigned int coinCounter = 0;
	unsigned int doorCounter = 0;

	for (size_t y = 0; y < countLines(map); y++)
	{
		for (size_t x = 0; x < strlen(map[y]); x++)
		{
			if (map[y][x] == 'P')
				++playerCounter;
			else if (map[y][x] == 'C')
				++coinCounter;
			else if (map[y][x] == 'D')
				++doorCounter;
		}
	}

	if (playerCounter == 1 && coinCounter >= 1 && doorCounter == 1)
		return true;
	else
		return false;
}
