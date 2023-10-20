#include "shell.h"

/**
  * print_env - Prints the environment variables
  * @env: Arguments
  */

void print_env(char **env)
{
	while (*env != NULL)
	{
		write(1, *env, strlen(*env));
		write(1, "\n", 1);
		env++;
	}
}


/**
  * handle_exit - Handles the exit functionality
  * @input: Input value to handle
  * @exit_status: Exit status of the code
  */

void handle_exit(char *input, int exit_status)
{
	free(input);
	exit(exit_status);
}

/**
  * shell_exit - Handles the exit status
  * @args: Arguments to the function
  * @input: Checks the status of exit
  *
  * Return: Status of exit, 1 if otherwise
  */

int shell_exit(char **args, char *input)
{
	char *status_str;
	int exit_status, i;

	if (args[1] != NULL)
	{
		exit_status = 0;
		status_str = args[1];

		for (i = 0; status_str[i] != '\0'; i++)
		{
			if (status_str[i] >= '0' && status_str[i] <= '9')
			{
				exit_status = exit_status * 10 + (status_str[i] - '0');
			}
			else
			{
				write(2, args[0], strlen(args[0]));
				write(2, ": exit: Illegal numer: ", 23);
				write(2, status_str, strlen(status_str));
				write(2, "\n", 1);
				handle_exit(input, 2);

				return (1);
			}
		}
		handle_exit(input, exit_status);
	}
	else
	{
		handle_exit(input, 0);
	}
	return (1);
}

/**
  * handle_cd - Handles the cd functionality
  * @args: Array of commands
  * @num_args: Argument count
  */

void handle_cd(char **args, int num_args)
{
	const char *home_dir, *prev_dir;

	home_dir = getenv("HOME");
	prev_dir = getenv("OLDPWD");

	if (num_args == 1 || strcmp(args[1], "~") == 0)
	{
		if (!home_dir)
		{
			perror("Home environment not set");
			return;
		}
		if (chdir(home_dir) != 0)
			perror("cd");
	}
	else if (num_args == 2 && strcmp(args[1], "-") == 0)
	{
		if (!prev_dir)
		{
			perror("OLDPWD environment not set");
			return;
		}
		if (chdir(prev_dir) != 0)
			perror("cd");
	}
	else
	{
		if (chdir(args[1]) != 0)
			perror("cd");
	}
}
