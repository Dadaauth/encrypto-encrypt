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

char *emptyline(char *txt, char *keyd);

// tools
char **get_cmdline(size_t *tok_count);
int interactive_mode();
void exit_program(char **stream);
void execute(char **stream, size_t tok_count);

// utils
size_t file_size(FILE *file);
void free_stream(char **stream);
char *remove_newline(char *str);


#endif