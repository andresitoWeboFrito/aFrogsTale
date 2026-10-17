#include "aFrogsTale.h"

// load a map from memory
char **loadMap(char *path)
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
		// problem opening the file, send and error TODO:
	}

	while (fgets(buffer, sizeof(buffer), mapFile))
	{
		// make the map a line bigger
		map = reallocMap(map);
		if (!map)
		{
			// TODO: reallocation failed do something about it
			printf("Couldn't realocate the map\n");
			return (NULL);
		}

		// Copy the content of the buffer into a line
		line = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
		if (!line)
		{
			// Failed allocation of line. TODO: something about it?
			return NULL;
		}
		strcpy(line, buffer);

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
	{ // failed creating the map. TODO: do something about it
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

// checks for a valid map?

// render map