#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../main.h"
#include "../algorithms/ceaser_cipher/ceaser.h"
#include "../algorithms/rijndael/rijndael.h"

void execute(char **stream, size_t tok_count)
{
    int i = 0;
    bool command_found = false;
    char *args[2] = {NULL, NULL};
    command commands[] = {
        {"encrypt", rijndael_encrypt},
        {"decrypt", rijndael_decrypt},
        {"", emptyline},
        {NULL, NULL},
    };

    if (tok_count >= 2)
        args[0] = stream[1];
    if (tok_count >= 3)
        args[1] = stream[2];

    while (commands[i].name != NULL)
    {
        if (strcmp(commands[i].name, stream[0]) == 0)
        {   
            commands[i].func_ptr(args[0], args[1]);
            command_found = true;
            break;
        }
        i++;
    }
    if (!command_found)
        fprintf(stderr, "command not found: %s\n", stream[0]);
}