#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "main.h"

/**
 * decrypt - decrypts an encrypted string of text.
 * @filename: the name of the file in which the text was encoded
 * @key: The key needed to unlock the encoded text
 * Return: The Unlocked text
*/
char *decrypt(char *filename, int key)
{
    int ch, i = 0;
    FILE *fptr, *decfptr;
    size_t fileCharCount;
    char *decryptedFile = strdup(filename), *decryptedTxt;

    strcat(decryptedFile, ".decr");
    if ((fptr = fopen(filename, "r")) == NULL)
    {
        printf("File Open Failed: %s\n", filename);
        return (NULL);
    }
    if ((decfptr = fopen(decryptedFile, "w")) == NULL)
    {
        printf("Failed to create enc file: %s\n", decryptedFile);
        return (NULL);
    }

    fileCharCount = file_size(fptr);
    decryptedTxt = malloc(sizeof(char) * fileCharCount);
    while ((ch = fgetc(fptr)) != EOF)
    {
        decryptedTxt[i] = ch - key;
        fputc(decryptedTxt[i], decfptr);
        i++;
    }
    decryptedTxt[i] = '\0';
    fclose(fptr);
    fclose(decfptr);
    return (decryptedTxt);
}