#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rijndael.h"
// Store plaintext length
// Store IV information
// Store ciphertext length
// Create a structure to handle the payload


void input_metadata(FILE *fileptr, metadata metadata)
{
    char *metadata_str = NULL;
    char *padding_bg = ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    char *padding_end = "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n//end//";
    char *divisor = "\n>>><<<\n";
    int total_length;
    int ciphertext_len_l, plaintext_len_l, divisor_len, padding_len, iv_len;
    int count_of_metadata = 3;

    iv_len = metadata.iv_length;
    ciphertext_len_l = snprintf(NULL, 0, "%d", metadata.ciphertext_len);
    plaintext_len_l = snprintf(NULL, 0, "%d", metadata.plaintext_len);
    divisor_len = strlen(divisor) * (count_of_metadata - 1);
    padding_len = strlen(padding_bg) + strlen(padding_end);

    total_length = iv_len + ciphertext_len_l + plaintext_len_l + divisor_len + padding_len;
    metadata_str = malloc(sizeof(char) * (total_length + 1));
    // Order of insertion IV >> Ciphertext Length >> Plaintext Length //
    snprintf(metadata_str, total_length + 1, "%s%s%s%d%s%d%s", padding_bg, metadata.iv, divisor, metadata.ciphertext_len, divisor, metadata.plaintext_len, padding_end);
    fprintf(fileptr, "%s", metadata_str);
}