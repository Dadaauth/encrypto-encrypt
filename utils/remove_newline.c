#include <stdio.h>
#include <string.h>
/**
 * remove_newline - removes the newline character from a string
 * @str: the string to work on
 * Return: the new string without the newline character
*/
char *remove_newline(char *str)
{
    int len = strlen(str);

    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';

    return (str);
}