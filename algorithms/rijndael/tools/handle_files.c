#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "tools.h"

/**
 * read_file_ded - read file, for decryption. I.E Read ciphertext
 * from file to be ready for decryption process (read_file_decrypted)/(read_file_ded)
 * @filename: the name OF the file to work on
 * Return: A character pointer (char *) containing the data
 * read from the file
*/
char *read_file_ded(char *filename)
{
    char *file_contents = NULL, buffer[1];
    int length = 0;
    FILE *fileptr = fopen(filename, "rb"); // open in binary mode because encrypted text may contain binary data.

    if (fileptr == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return (NULL);
    }

    // Read The File Contents And Save Into A String, however long it may be.
    /* It is safer to use fread instead of fgets because it is an encrypted file data*/
    while (fread(buffer, 1, 1, fileptr) > 0)
    {
        file_contents = realloc(file_contents, sizeof(char) * (length + 1));
        if (file_contents == NULL)
        {
            fprintf(stderr, "Error allocating memory: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        memcpy(file_contents + length, buffer, 1);
        length++;
    }
    fclose(fileptr);
    return (file_contents);
}
/**
 * read_file_end - read file, for encryption. I.E Read plaintext
 * from file to be ready for encryption process(read_file_encrypted)/(read_file_end)
 * @filename: the name fo the file to work on
 * Return: A character pointer (char *) containing the data
 * read from the file
*/
char *read_file_end(char *filename)
{
    char *file_contents = NULL;
    char buffer[255];
    int length = 0;
    FILE *fileptr;

    // Open The File And Check For Error That May Occur
    if ((fileptr = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return (NULL);
    }
    // Read The File Contents And Save Into A String, however long it may be.
    while (fgets(buffer, sizeof(buffer), fileptr) != NULL)
    {
        file_contents = realloc(file_contents, sizeof(char) * ((file_contents? strlen(file_contents) : 0) + strlen(buffer) + 1));
        if (file_contents == NULL)
        {
            fprintf(stderr, "Error allocating memory: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        memcpy(file_contents + length, buffer, strlen(buffer));
        length += strlen(buffer);
    }
    fclose(fileptr);
    return (file_contents);
}


/**
 * write_file_ded - write into file, for decryption. I.E write decrypted
 * text into a file (write_file_decrypted)/(write_file_ded)
 * @filename: the name of the file to operate on
 * @contents: the contents to write into @filename
 * Return: None
*/
void write_file_ded(char *filename, char *contents)
{
    FILE *fileptr;
    if ((fileptr = fopen(filename, "w")) == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    fprintf(fileptr, "%s", contents);
    fclose(fileptr);
}
/**
 * write_file_end - write into file, for encryption. I.E write encrypted
 * text into a file (write_file_encrypted)/(write_file_end)
 * @filename: the name of the file to operate on
 * @contents: the contents to write into @filename
 * Return: None
*/
void write_file_end(char *filename, char *contents, size_t length, metadata metadata)
{
    size_t bytes_written;
    FILE *fileptr = fopen(filename, "wb");

    if (fileptr == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    bytes_written = fwrite(contents, 1, length, fileptr);
    if (bytes_written != length)
    {
        fprintf(stderr, "Error writing to file (%s): %s\n", filename, strerror(errno));
        exit(EXIT_FAILURE);
    }
    rewind(fileptr);
    input_metadata(fileptr, metadata);
    fclose(fileptr);
}


/**
 * handle_files - handles opening the file for encryption and writing to a new file
 * for encryption
 * 
*/
char *handle_files(char *filename, char *contents, size_t content_len, mode mode, metadata metadata)
{
    if (contents == NULL) // Read file
    {
        char *file_contents;
        if (mode == ENCRYPT)
            file_contents = read_file_end(filename);
        else if (mode == DECRYPT)
            file_contents = read_file_ded(filename);
        return (file_contents);
    }
    // Write to file
    if (mode == ENCRYPT)
        write_file_end(filename, contents, content_len, metadata);
    else if (mode == DECRYPT)
        write_file_ded(filename, contents);
    return (NULL);
}