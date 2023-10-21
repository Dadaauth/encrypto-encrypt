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

int interactive_mode()
{
    int stop = false;
    char *ps1 = ">>! ";
    char **stream;
    size_t tok_count;

    printf("Encrypto:\n");
    printf("--------------------------------\n");

    while (!stop)
    {
        printf("%s", ps1);

        stream = get_cmdline(&tok_count);
        execute(stream, tok_count);
        free_stream(stream);
    }
}
