#include "shell.h"

/**
 * _putchar - Writes the character c to STDOUT
 * @c: The character to print
 *
 * Return: 1 on success. On error -1 is returned
 * errno is set appropriately
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * user_prompt - Display a prompt for the user to indicate
 * that the shell is ready to accept input
 *
 * This function checks if the standard input and uotput
 * are associated with terminal devices. If they are set interactive
 * flag to 1 and display prompt.
 *
 * Return: (Success)
 */

void user_prompt(void)
{
	/* Check if both stdin and stdout are associated with terminals */
	if (isatty(STDIN_FILENO) == 1 && isatty(STDOUT_FILENO) == 1)
	{
		flags.interactive = 1;
	}

	/* If the interactive flag is set, display the shell prompt */
	if (flags.interactive)
	{
		write(STDERR_FILENO, "myShell$ ", 9);
		/* Display the prompt on error */
	}
}
