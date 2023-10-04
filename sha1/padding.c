#include "sha1.h"

void padding(unsigned char *message, unsigned char *padded_message, uint64_t mlen, uint64_t padding_len){
    uint64_t i,j;

    for(i=0;i< mlen;i++)
	padded_message[i] = message[i];
    padded_message[i++] = 0x80;
    for(;i < (mlen + padding_len);i++)
	padded_message[i] = 0x00;
    j = mlen * 8;
    i = i + 7;
    for(;i >= (mlen + padding_len); i--){
        padded_message[i] = j & 0xff;
	j = j >> 8;
    }
}		
