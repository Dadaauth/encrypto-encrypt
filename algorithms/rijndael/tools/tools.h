#ifndef TOOLS_H
#define TOOLS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../rijndael.h"

/**
 * enum mode - defines the mode or status of the operation being performed
 * @ENCRYPT: encryption mode
 * @decrypt: decryption mode
*/
typedef enum mode {
    ENCRYPT,
    DECRYPT
} mode;

/**
 * struct metadata - a data structure for handling the metadata
 * to be inserted and removed from our encrypted text
 * @iv: the initialization vector
 * @iv_length: the length of the initialization vector
 * @ciphertext_len: the length of the ciphertext
 * @plaintext_len: the length of the plaintext
*/
typedef struct metadata {
    char *iv;
    size_t iv_length;
    size_t ciphertext_len;
    size_t plaintext_len;
} metadata;

void generate_random_iv(unsigned char *iv, size_t iv_length);
char *extract_iv(char *filename);
bool valid_arguments(char *filename, char *keyd, mode mode);


// File handling functions
char *handle_files(char *, char *, size_t, mode, metadata);
char *read_file_ded(char *filename);
//        ------------------        //
bool check_file_extension(const char *filename);
void input_metadata(FILE *fileptr, metadata metadata);
metadata extract_metadata(char *filename);

// Global Variables
extern char *padding_bg;
extern char *padding_end;
extern char *divisor;

#endif