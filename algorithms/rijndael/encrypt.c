#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include "rijndael.h"



/**
 * rijndael_encrypt - encrypts a file or string of text using
 * the secure AES rijndael encryption/decryption algorithm.
 * @filename: the name of the file you want to encrypt
 * @keyd: the key to encrypt the file contents or text
 * Return: the name of the resulting encrypted file. or NULL if error.
*/
char *rijndael_encrypt(char *filename, char *keyd)
{
    // Declare Primary Variables
    unsigned char *plaintext;
    int plaintext_len, ciphertext_len, len;
    const unsigned char *key = (const unsigned char *)keyd;
    size_t iv_length = 16;
    unsigned char iv[iv_length];
    mode mode = ENCRYPT;
    metadata metadata;


    OpenSSL_add_all_algorithms();
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    
    generate_random_iv(iv, iv_length);

    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    // Reading Files
    plaintext = (unsigned char *)handle_files(filename, NULL, 0, mode, metadata);
    if (plaintext == NULL)
        return (NULL);
    plaintext_len = strlen((char *)plaintext);

    // Encryption
    unsigned char ciphertext[plaintext_len + EVP_CIPHER_block_size(EVP_aes_256_cbc())];
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);
    ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    // Writing encrypted text to file
    metadata.iv = iv;
    metadata.iv_length = iv_length;
    metadata.ciphertext_len = (size_t) ciphertext_len;
    metadata.plaintext_len = (size_t) plaintext_len;
    handle_files(strcat(filename, ".enc"), ciphertext, ciphertext_len, mode, metadata);

    // Finalize Encryption
    EVP_CIPHER_CTX_free(ctx);
}