#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

typedef struct operation{
    char *name;
    char *(*func_ptr)(char*, char*);
} command;

char *encrypt(char *filename, char *keyd);
char *decrypt(char *filename, char *keyd);
char *emptyline(char *txt, char *keyd);

char **get_cmdline();
int interactive_mode();
void exit_program();

void execute(char **stream);

// utils
size_t file_size(FILE *file);
void free_stream(char **stream);
char *remove_newline(char *str);


#endif