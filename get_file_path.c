#include "shell.h"

/**
  * loc - Searches for the executable in each directory
  * @path: path argument
  * @arg: arg argument
  *
  * Return: Full path of executable
  */

char *loc(char *path, char *arg)
{
	char *cpy_path, *pathToken, *path_of_file;
	char *delim = ":";
	struct stat file;

	cpy_path = strdup(path);

	pathToken = strtok(cpy_path, delim);

	path_of_file = malloc(strlen(arg) + strlen(pathToken) + 2);

	if (!path_of_file)
	{
		perror("Memory allocation error");
		free(cpy_path);
		return (NULL);
	}

	while (pathToken != NULL)
	{
		strcpy(path_of_file, pathToken);
		strcat(path_of_file, "/");
		strcat(path_of_file, arg);
		strcat(path_of_file, "\0");

		if (stat(path_of_file, &file) == 0 &&
				access(path_of_file, X_OK) == 0)
		{
			free(cpy_path);
			return (path_of_file);
		}
		pathToken = strtok(NULL, delim);
	}

	free(path_of_file);
	free(cpy_path);
	return (NULL);
}

/**
  * find_loc - Correctly gets the PATH env variable
  * @arg: Arg passed to the function
  *
  * Return: Call loc function to search
  */

char *find_loc(char *arg)
{
	char *path;

	path = getenv("PATH");

	if (arg[0] == '/')
	{
		if (access(arg, X_OK) == 0)
			return (arg);
	}

	if (!path)
	{
		perror("PATH environment variable not found");
		return (NULL);
	}

	return (loc(path, arg));

}
