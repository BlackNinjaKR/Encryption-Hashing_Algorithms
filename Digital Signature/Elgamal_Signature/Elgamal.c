/*
    ElGamal Digital Signature using PBC Library

    Uses:
    - Pairing-based group G1
    - SHA256 hashing
    - Separate functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <pbc/pbc.h>
#include <openssl/sha.h>

/* Global Variables */

pairing_t pairing;

element_t g;   // generator
element_t x;   // private key
element_t y;   // public key

/* Initialize pairing */

void init_pairing()
{
    FILE *fp = fopen("param/a.param", "r");
    if (!fp)
    {
        printf("Error opening parameter file.\n");
        exit(1);
    }
    char param[1024];
    size_t count = fread(param, 1, 1024, fp);
    fclose(fp);
    pairing_init_set_buf(pairing, param, count);
}

/* Hash message to Zr */

void hash_message(const char *message, element_t hash)
{
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)message,strlen(message),digest);
    element_from_hash(hash,digest,SHA256_DIGEST_LENGTH);
}

/* Generate generator */

void generate_parameters()
{
    element_init_G1(g, pairing);

    // Random generator
    element_random(g);

    printf("\nSystem Parameters Generated\n");
}

/* Key Generation */

void generate_keys()
{
    element_init_Zr(x, pairing);
    element_init_G1(y, pairing);

    // Private key
    element_random(x);

    // Public key y = g^x
    element_pow_zn(y, g, x);

    printf("\nKeys Generated\n");
}

/* Signature Generation */
void sign_message(const char *message,element_t r,element_t s)
{
    element_t k;
    element_t hash;
    element_t temp;

    element_init_Zr(k, pairing);
    element_init_Zr(hash, pairing);
    element_init_Zr(temp, pairing);

    // Hash message
    hash_message(message, hash);

    while (1)
    {
        // Random k
        element_random(k);

        // r = g^k
        element_pow_zn(r, g, k);

        // temp = x * r
        element_mul(temp, x, r);

        // temp = H(m) - x*r
        element_sub(temp, hash, temp);

        // s = k^-1 * temp
        element_invert(k, k);
        element_mul(s, k, temp);

        // If s != 0 break
        if (!element_is0(s))
            break;
    }

    element_clear(k);
    element_clear(hash);
    element_clear(temp);

    printf("\nMessage Signed\n");
}

/* Signature Verification */

int verify_signature(const char *message,element_t r,element_t s)
{
    element_t hash;
    element_t left, right;
    element_t yr, rs;

    element_init_Zr(hash, pairing);

    element_init_G1(left, pairing);
    element_init_G1(right, pairing);
    element_init_G1(yr, pairing);
    element_init_G1(rs, pairing);

    // Hash message
    hash_message(message, hash);

    // left = g^H(m)
    element_pow_zn(left, g, hash);

    // yr = y^r
    element_pow_zn(yr, y, r);

    // rs = r^s
    element_pow_zn(rs, r, s);

    // right = y^r * r^s
    element_mul(right, yr, rs);

    int result = element_cmp(left, right) == 0;

    element_clear(hash);
    element_clear(left);
    element_clear(right);
    element_clear(yr);
    element_clear(rs);

    return result;
}

/* Main */

int main()
{
    init_pairing();

    generate_parameters();

    generate_keys();

    const char *message = "Hello ElGamal Signature using PBC";

    element_t r, s;

    element_init_G1(r, pairing);
    element_init_Zr(s, pairing);

    sign_message(message, r, s);

    printf("\nSignature:\n");
    element_printf("r = %B\n", r);
    element_printf("s = %B\n", s);

    int valid = verify_signature(message, r, s);

    if (valid)
        printf("\nSignature Verified: VALID\n");
    else
        printf("\nSignature Verified: INVALID\n");
    
    return 0;
}