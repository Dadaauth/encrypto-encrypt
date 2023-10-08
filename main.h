#ifndef MAIN_H
#define MAIN_H

typedef struct operation{
    char *name;
    char *(*func_ptr)(char*, int);
} command;

char *encrypt(char *txt, int key);
char *decrypt(char *enctxt, int key);
size_t file_size(FILE *file);
int interactive_mode();
void free_stream(char **stream);

#endif