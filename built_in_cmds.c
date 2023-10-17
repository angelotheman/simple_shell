#include "shell.h"

/**
  * print_env - Prints the environment variables
  * @env: Arguments
  */

void print_env(char **env)
{
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}


/**
  * handle_exit - Handles the exit functionality
  * @input: Input value to handle
  */

void handle_exit(char *input)
{
	free(input);
	exit(0);
}

/**
  * handle_cd - Handles the cd functionality
  * @args: Array of commands
  * @num_args: Argument count
  */

void handle_cd(char **args, int num_args)
{
	if (num_args < 2)
	{
		perror("Needs two argument");
	}
	else
	{
		if (chdir(args[1]) != 0)
			perror("cd");
	}
}
