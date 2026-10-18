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
		printf("Couldnt open file\n");
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
	return line;
}

void parseMap(GameData *game)
{
	// TODO: this will do more things
	for (size_t y = 0; y < countLines(game->map); y++)
	{
		for (size_t x = 0; x < strlen(game->map[y]); x++)
		{
			if (game->map[y][x] == 'P')
			{
				game->playerPos.x = x;
				game->playerPos.y = y;
			}
		}
	}
}

// TODO:  checks for a valid map?
