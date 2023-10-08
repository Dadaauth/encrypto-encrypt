#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * file_size - gets the amount of characters in a file
 * @file: the name of the file
 * Return: the size of the file
*/
size_t file_size(FILE *file)
{
    size_t size = 0;

    while (fgetc(file) != EOF)
    {
        size++;
    }
    rewind(file);
    return (size);
}