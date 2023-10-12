#include "shell.h"

/**
 * main - Display the prompt before reading and processing user input
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: Environment vector
 *
 * Return: 0 (Success)
 */
int main(int argc, char **argv, char *envp[])
{
	char commnd[128];

	signal(SIGINT, signal_handler);

	while (1)
	{
		/* Display the shell prompt */
		prompt_user();
	}
	if (fgets(input, sizeof(input), stdin) == NULL)
		break;

	size_t len = strlen(input);
	if (len > 0 && input[len - 1] == '\n')
		input[len - 1] = '\0';

	return (0);
}
