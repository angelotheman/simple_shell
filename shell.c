#include "shell.h"

/**
  * main - Wait program
  * @argc: Argumnt count
  * @argv: Array of arguments
  *
  * Return: O Always succes
  */

int main(int argc, char *argv[], char **env)
{
	ssize_t nread;
	char *buf = NULL;
	size_t count = 0;
	int i, status, line_number = 1;
	pid_t child_pid;
	char *token;
	char **array;
	(void)argc, (void)argv;

	while (1)
	{
		if (isatty(0))
			write(1, "MyShell$ ", 9);

		nread = getline(&buf, &count, stdin);
		if (nread == -1 || strcmp(buf, "exit\n") == 0)
		{
			free(buf);
			exit (0);
		}
		
		if (strcmp(buf, "env\n") == 0)
		{
			print_env(env);
			continue;
		}

		token = strtok(buf, " \n");

		array = malloc(sizeof(char *) * 1024);
		i = 0;
		while (token)
		{
			array[i] = token;
			if (i == 0)
				array[0] = getFilePath(array[0]);
			token = strtok(NULL, " \n");
			i++;
		}
		array[i] = NULL;

		for (i = 0; array[i] != NULL; i++)
			printf("%s\n", array[i]);

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error: Failed to create");
			exit(41);
		}
		if (child_pid == 0)
		{
			/* if (execve(array[0], array, NULL) == -1) */
			if (execvp(array[0], array) == -1)
			{
				perror("Error: Failed");
				exit(7);
			}
		}
		else
		{
			wait(&status);
		}
		line_number++;
		free(array);
	}
	return (0);
}
