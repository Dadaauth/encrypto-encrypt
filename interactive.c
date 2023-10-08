/**
 * This mode is mainly for when the user enters the name of the program
 * without specifying a filename. It can also be self induced with a command.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>
#include "main.h"
void execute(char **stream);
int interactive_mode()
{
    char *command = NULL, **stream = calloc(1, sizeof(char *)), **new_stream;
    int llen, stop = false, i = 0;
    size_t len = 0;
    char *ps1 = ">>> ";

    printf("Encrypto:\n");
    printf("--------------------------------\n");

    while (!stop)
    {
        printf("%s", ps1);
        llen = getline(&command, &len, stdin);
        i = 0;
        stream[i] = strtok(command, " ");
        if (strcmp(stream[i], "exit\n") == 0)
            exit(EXIT_SUCCESS);
        while (stream[i] != NULL)
        {
            i++;
            new_stream = realloc(stream, sizeof(char*) * (i + 1));
            if (new_stream == NULL)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
            stream = new_stream;
            stream[i] = strtok(NULL, " ");
        }
        execute(stream);
        free_stream(stream);
    }
}

void execute(char **stream)
{
    bool command_found = false;
    command commands[] = {
        {"encrypt", encrypt},
        {"decrypt", decrypt},
        {NULL, NULL},
    };
    int i = 0;
    if (stream[0][strlen(stream[0]) - 1] = '\n')
    {
        printf("It has newline %s", stream[0]);
        stream[0][strlen(stream[0]) - 1] = '\0';
        printf("It has newline %s", stream[0]);
    }
    while (commands[i].name != NULL)
    {
        if (strcmp(commands[i].name, stream[0]) == 0)
        {
            if (stream[1] == NULL || stream[2] == NULL)
            {
                printf("Error: Please provide arguments to the %s command.\n", commands[i].name);
                return;
            }
            commands[i].func_ptr(stream[1], atoi(stream[2]));
            command_found = true;
            break;
        }
        i++;
    }
    if (!command_found)
    {
        printf("Command Not Found: %s\n", stream[0]);
    }
}
// 143fcbchel34141
