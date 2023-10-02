#include "aes.h"

void XOR(unsigned char *A, unsigned char *B, unsigned char *C){
    for(uint8_t i=0; i< 16; i++)
        C[i] = A[i] ^ B[i];
}

