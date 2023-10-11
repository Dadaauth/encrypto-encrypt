#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "../../main.h"
/**
 * encrypt - encrypts a string of text
 * @filename: the file containing the text to encrypt
 * @key: The key for encryption
 * Return: The Encrypted File Name
*/
char *encrypt(char *filename, char *keyd)
{
    int ch, i = 0, key;
    FILE *fptr, *encfptr;
    size_t fileCharCount;
    char *encryptedFile, *encryptedTxt;

    if (filename == NULL || keyd == NULL)
    {
        printf("Error: Please provide arguments to the encrypt command.\n");
        return (NULL);
    }

    key = atoi(keyd);
    encryptedFile = strdup(filename);
    strcat(encryptedFile, ".enc");
    if ((fptr = fopen(filename, "r")) == NULL)
    {
        printf("File Open Failed: %s\n", filename);
        return (NULL);
    }
    if ((encfptr = fopen(encryptedFile, "w")) == NULL)
    {
        printf("Failed to create enc file: %s\n", encryptedFile);
        return (NULL);
    }

    fileCharCount = file_size(fptr);
    encryptedTxt = malloc(sizeof(char) * fileCharCount);
    while ((ch = fgetc(fptr)) != EOF)
    {
        encryptedTxt[i] = ch + key;
        fputc(encryptedTxt[i], encfptr);
        i++;
    }
    encryptedTxt[i] = '\0';
    fclose(fptr);
    fclose(encfptr);
    return (encryptedFile);
}

