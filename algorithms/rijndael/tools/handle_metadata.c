#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include "tools.h"
#include "metadata_tools.h"

char *padding_bg = "<-----metadata start----->";
char *padding_end = "<-----metadata end----->";
char *divisor = ">>>|<<<";
/**
 * input_metadata - input metadata into encrypted text file
 * @fileptr: the file pointer to the file to input the metadata
 * @metadata: the metadata to input into the file
*/
void input_metadata(FILE *fileptr, metadata metadata)
{
    char *metadata_str = NULL;
    int total_length;
    int ciphertext_len_l, plaintext_len_l, divisor_len, padding_len, iv_len;
    int count_of_metadata = 3;

    iv_len = metadata.iv_length;
    ciphertext_len_l = snprintf(NULL, 0, "%d", metadata.ciphertext_len);
    plaintext_len_l = snprintf(NULL, 0, "%d", metadata.plaintext_len);
    divisor_len = strlen(divisor) * (count_of_metadata - 1);
    padding_len = strlen(padding_bg) + strlen(padding_end);

    total_length = iv_len + ciphertext_len_l + plaintext_len_l + divisor_len + padding_len;
    metadata_str = malloc(sizeof(char) * (total_length + 20));
    // Order of insertion IV >> Ciphertext Length >> Plaintext Length //
    snprintf(metadata_str, total_length + 20, "%s%s%s%d%s%d%s", padding_bg, metadata.iv, divisor, metadata.ciphertext_len, divisor, metadata.plaintext_len, padding_end);
    fprintf(fileptr, "%s", metadata_str);
    free(metadata_str);
}

/**
 * extract_metadata - extracts the metadata from the encrypted text file
 * @filename: the name of the file to extract the metadata from
 * Return: the metadata struct data extracted from the file
*/
metadata extract_metadata(char *filename)
{
    metadata metadata = {NULL, 0, 0, 0};
    char *file_contents = NULL;
    char *metadata_contents;
    long unsigned fc_length;
    size_t cursor;

    fc_length = read_enc_file(filename, &file_contents); // if fc_length == 0. An error occured
    if (fc_length == 0)
    {
        // Error Occured since the length of the data read from
        // the file is zero(0)
    }
    if(!check_metadata_begin(file_contents, &cursor) || !check_metadata_end(file_contents, fc_length, &cursor))
        return (metadata);

    // extract_md_string(file_contents, cursor, &metadata_contents);
    // Order of extraction IV >> Ciphertext Length >> Plaintext Length //
    // printf("md_string: %s\n", metadata_contents);
    // file_contents += cursor;
    exit(EXIT_SUCCESS);
}


