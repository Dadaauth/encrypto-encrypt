#include <string.h>
#include <errno.h>
#include <openssl/rand.h>
#include "rijndael.h"

/**
 * generate_random_iv - generates a random Initialization Vector (IV)
 * for each encryption process
 * @iv: a pointer to a char array where to save the generated IV.
 * @iv_length: the length of the IV
 * 
*/
void generate_random_iv(unsigned char *iv, size_t iv_length)
{
    if (RAND_bytes(iv, (int) iv_length) != 1)
    {
        fprintf(stderr, "Error generating random bytes for IV: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}