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
			if (status_str[i] < '0' || status_str[i] > '9')
			{
				handle_exit(input, 2);
				return (1);
			}
			exit_status = exit_status * 10 + (status_str[i] - '0');
		}
		handle_exit(input, exit_status);
	}
	else
	{
		handle_exit(input, 127);
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

/**
  * my_getline - Works like the getline function
  * @line: The line input
  * @len: The size of the input
  * @stream: The stream
  *
  * Return: Size of input buffer
  */

ssize_t my_getline(char **line, size_t *len, FILE *stream)
{
	ssize_t chars_read;
	size_t new_len;
	char *new_line;
	int c;

	if (!line || !len)
	{
		errno = EINVAL;
		return (-1);
	}

	if (*line == NULL)
	{
		*len = 128;
		*line = (char *)malloc(*len);
		if (*line == NULL)
			return (-1);
	}
	
	chars_read = 0;

	while ((c = fgetc(stream)) != EOF)
	{
		if ((size_t)chars_read >= *len - 2)
		{
			new_len = *len * 2;
			new_line = (char *)realloc(*line, new_len);
			if (new_line == NULL)
				return (-1);
			*line = new_line;
			*len = new_len;
		}

		(*line)[chars_read++] = (char)c;

		if (c == '\n')
		{
			(*line)[chars_read] = '\0';
			return (chars_read);
		}
	}
	if (chars_read == 0)
		return (-1);

	(*line)[chars_read] = '\0';
	return (chars_read);
}
