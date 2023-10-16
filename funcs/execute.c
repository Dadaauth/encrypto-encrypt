#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../main.h"
#include "../algorithms/rijndael/rijndael.h"

void execute(char **stream)
{
    int i = 0;
    bool command_found = false;
    command commands[] = {
        {"encrypt", rijndael_encrypt},
        {"decrypt", decrypt},
        {"", emptyline},
        {NULL, NULL},
    };

    while (commands[i].name != NULL)
    {
        if (strcmp(commands[i].name, stream[0]) == 0)
        {   
            commands[i].func_ptr(stream[1], stream[2]);
            command_found = true;
            break;
        }
        i++;
    }
    if (!command_found)
        printf("Command Not Found: %s\n", stream[0]);
}