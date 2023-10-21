#include <stdio.h>
#include <stdlib.h>
#include "../main.h"

void exit_program(char **stream)
{
    free_stream(stream);
    printf("Thank you for using Encrypto!\n, Bye!!");
    exit(EXIT_SUCCESS);
}