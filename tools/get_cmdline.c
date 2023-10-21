#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../main.h"
char* get_user_input();
/**
 * get_cmdline - gets the command on the cmdline
 * from the user and tokennizes it into a double pointer
 * of strings
 * Return: the double pointer of strings which contains the command
 * to run and its arguments
*/
char **get_cmdline(size_t *tok_count)
{
    int i = 0;
    char **stream = malloc(sizeof(char *)), **new_stream, *input;

    input = get_user_input();
    stream[i] = remove_newline(strtok(input, " "));
    while (stream[i++] != NULL)
    {
        new_stream = realloc(stream, sizeof(char*) * (i + 1));
        if (new_stream == NULL)
        {
            perror("realloc");
            exit(EXIT_FAILURE);
        }

        stream = new_stream;
        stream[i] = strtok(NULL, " ");
        
        if (stream[i] != NULL)
            stream[i] = remove_newline(stream[i]);
    }
    *tok_count = i - 1;
    if (strcmp(stream[0], "exit") == 0)
        exit_program(stream);
    return (stream);
}


/**
 * get_user_input - gets user input from stdin
 * Return: the user input / text
*/
char* get_user_input()
{
    char* input = NULL;
    size_t size = 0, llen;

    llen = getline(&input, &size, stdin);
    if (llen == -1)
    {
        perror("getline");
        exit(EXIT_FAILURE);
    }
    return (input);
}
