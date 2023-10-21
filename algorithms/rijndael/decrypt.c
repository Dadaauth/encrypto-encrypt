#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include "rijndael.h"
#include "tools/tools.h"
/**
 * rijndael_decrypt - decrypts a file or string of text using
 * the secure AES rijndael encryption/decryption algorithm.
 * @filename: the name of the file you want to decrypt
 * @keyd: the key to decrypt the file contents or text
 * Return: the name of the resulting decrypted file. Or NULL if error.
*/
char *rijndael_decrypt(char *filename, char *keyd)
{
    unsigned char *encryptedText;
    int plainText_len, encryptedText_len, iv_length = 16;
    const unsigned char *key;
    unsigned char iv[iv_length];
    metadata metadata;

    if (!valid_arguments(filename, keyd, DECRYPT))
        return (NULL);

    exit(EXIT_SUCCESS);
    OpenSSL_add_all_algorithms();
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    key = (const unsigned char *)keyd;
    // Reading Files
    if (!check_file_extension(filename))
    {
        fprintf(stderr, "File Extension Error: encrypted file name should end with '.enc'\n");
        return (NULL);
    }
    exit(EXIT_SUCCESS);
    metadata = extract_metadata(strdup(filename));
    // extract_iv(filename);
    // plainText_len = extract_plainText_len(filename);
    // encryptedText_len = extract_eTextLength(filename);
    encryptedText = (unsigned char *)handle_files(filename, NULL, 0, DECRYPT, metadata);
    if (encryptedText == NULL)
        return (NULL);

    // Decryption
    unsigned char decryptedText[plainText_len + 1];
    int len;
    EVP_DecryptUpdate(ctx, decryptedText, &len, encryptedText, encryptedText_len);
    int decrypted_len = len;
    EVP_DecryptFinal_ex(ctx, decryptedText + len, &len);
    decrypted_len += len;
    decryptedText[decrypted_len] = '\0';


    // Writing Encrypted Text to File

    // handle_files(strcat(filename, ".enc"), decryptedText);


    // Finalize Encryption
    EVP_CIPHER_CTX_free(ctx);
}