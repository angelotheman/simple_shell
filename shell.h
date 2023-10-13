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
void print_env(char **env);
char *find_loc(char *arg);
char *loc(char *path, char *arg);

#endif /* SHELL_H */
