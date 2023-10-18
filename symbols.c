#include "shell.h"

/**
  * handle_comment - Handles the '#' in the input
  * @input: Input value
  *
  * Return: The stripped down input
  */

char *handle_comment(char *input)
{
	char *comment_pos;

	comment_pos = strstr(input, " #");

	if (comment_pos)
	{
		*comment_pos = '\0';
	}

	return (input);
}
