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
	(void)argc, (void)argv;
	ssize_t nread;
	char *buf = NULL, *token, *path;
	size_t count = 0;
	int status, line_number = 1, i, j;
	pid_t child_pid;
	char *array[10];

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

		
		i = 0;
		while (buf[i] != '\n')
		{
			i++;
		}
		buf[i] = '\0';
		
		j = 0;
		token = strtok(buf, " \n");
		while (token)
		{
			array[j] = token;
			token = strtok(NULL, ":");
			j++;
		}
		array[j] = NULL;

		path = find_loc(array[0]);

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error: Failed to create");
			free(buf);
			exit(41);
		}
		if (child_pid == 0)
		{
			if (execve(path, array, NULL) == -1)
			/* if (execvp(array[0], array) == -1)*/
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
	}
	return (0);
}
