#include<stdio.h>
#include<stdint.h>
#include<string.h>

#define N 512
#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476

#define F(b,c,d) (((b) & (c)) | ((~(b)) & (d)))
#define G(b,c,d) (((b) & (d)) | ((c) & (~(d))))
#define H(b,c,d) ((b) ^ (c) ^ (d))
#define I(b,c,d) ((c) ^ ((b) | (~(d))))
#define rotate(r, s) (((r) << (s)) | ((r) >> (32 -(s))))

void md5_main(unsigned char *input);
void R1(uint32_t *X, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d);
void R2(uint32_t *X, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d);
void R3(uint32_t *X, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d);
void R4(uint32_t *X, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d);


