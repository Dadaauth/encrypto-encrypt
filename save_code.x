#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

int main() {
    OpenSSL_add_all_algorithms();

    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();

    const unsigned char *key = (const unsigned char *)"YourEncryptionKey";
    const unsigned char *iv = (const unsigned char *)"InitializationV";

    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    unsigned char *plaintext = (unsigned char *)"YourPlainText";
    int plaintext_len = strlen((char *)plaintext);

    unsigned char ciphertext[plaintext_len + EVP_CIPHER_block_size(EVP_aes_256_cbc())];
    int len;
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);
    int ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    printf("Ciphertext: ");
    for (int i = 0; i < ciphertext_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    unsigned char decryptedtext[plaintext_len];
    EVP_DecryptUpdate(ctx, decryptedtext, &len, ciphertext, ciphertext_len);
    int decrypted_len = len;
    EVP_DecryptFinal_ex(ctx, decryptedtext + len, &len);
    decrypted_len += len;
    decryptedtext[decrypted_len] = '\0';

    printf("Decrypted Text: %s\n", decryptedtext);

    EVP_CIPHER_CTX_free(ctx);

    return 0;
}
