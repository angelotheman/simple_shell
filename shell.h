#ifndef SHELL_H
#define SHELL_H

externchar **environ
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <signal.h>

int main(int argc, char **argv, char *envp[]);
int _putchar(char c);
void user_prompt(void);

#endif
