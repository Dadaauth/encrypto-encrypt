#ifndef RIJNDAEL_H
#define RIJNDAEL_H

typedef enum mode {
    ENCRYPT,
    DECRYPT
} mode;

// typedef enum payload_name {
//     IV,
//     CIPHERTEXT_LEN,
//     PLAINTEXT_LEN
// } payload_name;

// typedef struct payload {
//     payload_name payload_name;
//     char *data_str;
//     int data_int;
// } payload;

typedef struct metadata {
    char *iv;
    size_t iv_length;
    size_t ciphertext_len;
    size_t plaintext_len;
} metadata;


void generate_random_iv(unsigned char *iv, size_t iv_length);
char *extract_iv(char *filename);
char *rijndael_encrypt(char *filename, char *keyd);
char *handle_files(char *, char *, size_t, mode, metadata);
int check_file_extension(const char *filename);
void input_metadata(FILE *fileptr, metadata metadata);

#endif