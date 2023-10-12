#include "shell.h"

/**
  * startsWithForwardSlash - Checks if file starts with "/"
  * @str: The filename to be checked
  *
  * Return: 0 if yes and 1 if NO
  */

int startsWithForwardSlash(const char *str)
{
	if (str != NULL && str[0] == '/')
		return (1);

	return (0);
}

/**
  * getFilePath - Get the executable path of file
  * @file_name: The executable file
  *
  * Return: Full path to the executable file
  */

char *getFilePath(char *file_name)
{
	char *path = "/bin:";
	char *path_copy = NULL, *token, *new_Path = NULL;
	struct stat file_path;

	if (startsWithForwardSlash(file_name))
		return (file_name);

	path_copy = strdup(path);

	if (path)
	{
		token = strtok(path_copy, ":");

		while (token)
		{
			char path_buffer[100];

			strcat(path_buffer, token);
			strcat(path_buffer, "/");
			strcat(path_buffer, file_name);
			strcat(path_buffer, "\0");

			if (stat(path_buffer, &file_path) == 0 &&
				access(path_buffer, X_OK) == 0)
			{
				new_Path = strdup(path_buffer);
				break;
			}
			token = strtok(NULL, ":");
		}
		free(path_copy);
	}
	return (new_Path);
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
