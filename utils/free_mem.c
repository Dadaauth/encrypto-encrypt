#include <stdio.h>
#include <stdlib.h>


void free_stream(char **stream)
{
    int i = 0;

    while (stream[i] != NULL)
    {
        free(stream[i]);
        i++;
    }
    // free(stream);
}