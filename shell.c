#include "shell.h"

/**
  * main - Wait program
  * @argc: Argumnt count
  * @argv: Array of arguments
  * @env: Environment variable
  *
  * Return: O Always succes
  */

int main(int argc, char *argv[], char **env)
{
	char *input_buffer;
	(void)argc;

	while (1)
	{
		print_prompt();
		input_buffer = read_input();
		execute_command(input_buffer, argv, env);
		free(input_buffer);
	}

	return (0);
}
