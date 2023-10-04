#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdint.h>

//initial hash values
#define H0 0x67452301
#define H1 0xefcdab89
#define H2 0x98badcfe
#define H3 0x10325476
#define H4 0xc3d2e1f0

//Round functions
//#define Ch(x,y,z) (((x) & (y)) ^ ((x) & (z)))
#define Ch(x,y,z) ((x & (y ^ z)) ^ z)
#define Parity(x,y,z) ((x) ^ (y) ^ (z))
#define Maj(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

void sha1(unsigned char *message, uint32_t *hash, uint64_t mlen);
void padding(unsigned char *message, unsigned char *padded_message, uint64_t mlen, uint64_t padding_len);
void parsing(uint32_t *M, unsigned char *padded_message, uint64_t mlen);
void sha1_comp(uint32_t *M);
uint32_t RotLeft(uint32_t w, uint8_t n);



//HMAC Implementation
void hmac_main(unsigned char *text, uint32_t *hmac);
