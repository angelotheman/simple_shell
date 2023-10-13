#include "shell.h"

/**
  * startsWithForwardSlash - Checks if file starts with "/"
  * @str: The filename to be checked
  *
  * Return: 0 if yes and 1 if NO
  */

int startsWithForwardSlash(const char *str)
{
	if (str != NULL || str[0] == '/')
		return (1);

	return (0);
}

/**
  * getFilePath - Get the executable path of file
  * @file_name: The executable file
  *
  * Return: Full path to the executable file
  */

char *get_file_path(char *file_name)
{
	char *path = getenv("PATH");
	char *path_copy = NULL, *token; /*new_Path = NULL;*/
	struct stat file_path;
	
	if (startsWithForwardSlash(file_name) &&
			access(file_name, X_OK) == 0)
		return (file_name);

	
	if (path)
	{
		path_copy = strdup(path);
		token = strtok(path_copy, ":");
		char *path_buffer = malloc(strlen(token) + strlen(file_name) + 2);
		if (path_buffer == NULL)
		{
			perror("Error: malloc failed");
			exit(EXIT_FAILURE);
		}

		while (token)
		{	
			strcat(path_buffer, token);
			strcat(path_buffer, "/");
			strcat(path_buffer, file_name);
			strcat(path_buffer, "\0");

			if (stat(path_buffer, &file_path) == 0 &&
					access(path_buffer, X_OK) == 0)
			{
				free(path_copy);
				return (path_buffer);
			}
			
			token = strtok(NULL, ":");
		}
		free(path_buffer);
	}
	return (NULL);
}

/**
  * print_env - Prints the environment variables
  * @env: Arguments
  */

void print_env(char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		printf("%s\n", env[i]);
	}
}
