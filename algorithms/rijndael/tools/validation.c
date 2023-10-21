#include <string.h>
#include <stdbool.h>
#include "tools.h"
/**
 * valid_arguments - checks if the arguments provided to
 * the rijndael_encrypt function are valid
 * @filename: the name of the file you want to encrypt
 * @keyd: the key to encrypt the file contents or text
 * Return: true if valid arguments, false if not
*/
bool valid_arguments(char *filename, char *keyd, mode mode)
{
    bool arg_valid = true;
    char *process = (mode == ENCRYPT) ? "encryption" : (mode == DECRYPT) ? "decryption" : "unknown";

    if (filename == NULL)
    {
        printf("Please provide filename\n");
        arg_valid = false;
    }
    if (keyd == NULL)
    {
        printf("Please provide key for %s\n", process);
        arg_valid =  false;
    }
    if (!arg_valid)
    {
        printf("Usage: encrypto <filename> <key>\n");
        printf("...Using rijndael %s algorithm...\n", process);
    }
    return (arg_valid);
}
/**
 * check_file_extension - checks if the file extension is valid for
 * the decryption process
 * @filename: the name of the file to validate
 * Return: true if valid, false if not
*/
bool check_file_extension(const char *filename)
{
    int len = strlen(filename);
    
    if (len < 5)
    {
        return false;
    }
    return strcmp(filename + len - 4, ".enc") == 0;
}