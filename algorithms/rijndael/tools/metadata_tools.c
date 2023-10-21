#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include "tools.h"

/**
 * metadata_end - checks if the next string of character in our @file_contents
 * contains the metadata_end_indicator
 * @file_contents: a char pointer that holds the contents of the file
 * @char_count: a safety measure to know when we have reached the end
 * of a string to prevent any memory issues and infinite loop
 * Return: true or false
*/
bool metadata_end(char *file_contents, unsigned long char_count)
{
    char *retrieved = malloc(sizeof(char) * (strlen(padding_end) + 1));
    size_t i = 0;

    while (i < strlen(padding_end))
    {
        if (i > char_count)
            return (false);
        retrieved[i] = file_contents[i];
        i++;
    }
    retrieved[i] = '\0';
    return (strcmp(retrieved, padding_end) == 0);
}

/**
 * extract_md_string -  extracts the metadata without its paddings or 
 * beginning and ending indicators. ie extracts the middle data
 * @file_contents: a char pointer to the string of characters to work on
 * @cursor: the position of our cursor in the string
 * @md_contents: a pointer to the memory location of a variable
 * that is to hold the value of the extracted metadata
 * (again excluding the paddings[padding_bg and padding_end])
*/
void extract_md_string(char *file_contents, size_t cursor, char **md_contents)
{
    size_t metadata_len;
    int metadata_mid_len, j, i = strlen(padding_bg);
    char *metadata_contents;

    metadata_len = cursor;
    metadata_mid_len = metadata_len - (strlen(padding_bg) - strlen(padding_end));
    metadata_contents = malloc(sizeof(char) * (metadata_mid_len));
    if (metadata_contents == NULL)
    {
        fprintf(stderr, "Failed to allocate memory: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    for (j = 0; j < metadata_mid_len; j++, i++)
        metadata_contents[j] = file_contents[i];
    *md_contents = metadata_contents;
}

/**
 * check_metadata_begin - checks if the metadata begining indicator is
 * present in the string of characters
 * @file_contents: a char pointer holding the string of characters
 * @cursor: a pointer to the memory location of the cursor counting
 * how far we have gone in the string. This is added so we can updated
 * our cursor as we move through the string in this function
 * Return: true or false
*/
bool check_metadata_begin(char *file_contents, size_t *cursor)
{
    char *retrieved = malloc(sizeof(char) * (strlen(padding_bg) + 1));
    size_t i;

    for (i = 0; i < strlen(padding_bg); i++) 
        retrieved[i] = file_contents[i];
    retrieved[i] = '\0';
    *cursor += i;

    if (strcmp(retrieved, padding_bg) != 0)
    {
        fprintf(stderr, "encrypted file does not begin with metadata.\n");
        fprintf(stderr, "file has been tampered with\n");
        free(retrieved);
        return (false);
    }
    free(retrieved);
    return (true);
}

/**
 * check_metadata_end - checks if the metadata end indicator is present in
 * the string of characters
 * @file_contents: a char pointer that holds the string of characters to work on
 * @fc_length: @file_contents length
 * @cursor: a pointer to the memory location of the cursor counting
 * how far we have gone in the string. This is added so we can updated
 * our cursor after moving through the string in this function. It will also
 * indicate the length of our overall metadata string (including its padding)/
 * (start and end indicators)
 * Return: true or false
*/
bool check_metadata_end(char *file_contents, size_t fc_length, size_t *cursor)
{
    bool metadata_end_exists = false;
    size_t j = *cursor;

    while (j < (fc_length - *cursor))
    {
        if (file_contents[j] == '<')
        {
            if (metadata_end(file_contents + j, fc_length - j))
            {
                j += strlen(padding_end);
                metadata_end_exists = true;
                break;
            }
        }
        j++;
    }

    *cursor = j;
    if (!metadata_end_exists)
        fprintf(stderr, "file is wrongly formated\n metadata end indicator not found\n");

    return (metadata_end_exists);
}

/**
 * read_enc_file - reads a file containing encrypted text. This
 * function is only for the @extract_metadata function, as it is developed
 * specialy for it.
 * @filename: the name of the filw to work on
 * @file_contents: a pointer to a char pointer defined in the @extract_metadata
 * function.
 * Return: the length of the read encrypted file
*/
long unsigned read_enc_file(char *filename, char **file_contents)
{
    char buffer[1];
    int length = 0;
    FILE *fileptr = fopen(filename, "rb"); // open in binary mode because encrypted text may contain binary data.

    if (fileptr == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return (0);
    }

    // Read The File Contents And Save Into A String, however long it may be.
    /* It is safer to use fread instead of fgets because it is an encrypted file data*/
    while (fread(buffer, 1, 1, fileptr) > 0)
    {
        *file_contents = realloc(*file_contents, sizeof(char) * (length + 1));
        if (*file_contents == NULL)
        {
            fprintf(stderr, "Error allocating memory: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        memcpy((*file_contents) + length, buffer, 1);
        length++;
    }
    fclose(fileptr);
    return (length);
}