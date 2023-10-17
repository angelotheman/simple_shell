#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

/* Helper Functions */
int startsWithFowardSlash(char const *str);
char *get_file_path(char *file_name);
char *get_file_loc(char *path, char *file_name);
void execute_command(char *input, char **env);
char *read_input(void);
void print_prompt(void);
int tokenize_input(char *input, char *args[]);

/* Built in Functions */
int handle_builtin_commands(char **args, int num_args, char *input, char **env);
void print_env(char **env);
void handle_cd(char **args, int num_args);
void handle_exit(char *input);

#endif /* SHELL_H */
