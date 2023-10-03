#include "sha1.h"

//SHA1 constant
const uint32_t K[4] = {0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xca62c1d6};

uint32_t h0,h1,h2,h3,h4;

void sha1(unsigned char *message, unsigned char *hash){
    uint64_t mlen = strlen(message);
    uint64_t offset = mlen / 64;
    uint64_t lastblock = mlen % 64;
    uint64_t padding_len = lastblock < 56 ? 56 - lastblock : (56+64) - lastblock;
    uint64_t new_mlen = mlen + padding_len + 8;
    unsigned char padded_message[new_mlen];
    uint64_t i,j;
    printf("\nMessage Length: %ld",mlen);
    padding(message, padded_message, padding_len);
    //Print padded message
    printf("\npadded message : ");
    for(i=0; i < new_mlen;i++)
	printf("%2.2x ",padded_message[i]);

    //parsing padded message
    uint32_t M[new_mlen / 4];
    parsing(M, padded_message, new_mlen);
    //print parsed message
    printf("\nparsed message: ");
    for(i=0;i < new_mlen / 4; i++)
	printf("%08x ",M[i]);
    h0 = H0; h1 = H1; h2 = H2; h3 = H3; h4 = H4;
    //SHA1 computation
    for(i = 0; i < new_mlen / 64;i++)
	sha1_comp(&M[16 * i]);

    printf("\nHash : %08x %08x %08x %08x %08x\n",h0,h1,h2,h3,h4);

}

void parsing(uint32_t *M, unsigned char *padded_message, uint64_t mlen){
    uint64_t i;
    uint8_t j ;
    for(i = 0; i < mlen / 4; i++){
	M[i] = ((uint32_t)padded_message[4*i] << 24) ^ ((uint32_t)padded_message[4*i+1] << 16) ^ ((uint32_t)padded_message[4*i+2] << 8) ^ ((uint32_t)padded_message[4*i+3]);
    }
}    
void sha1_comp(uint32_t *M){
    //prepare message schedule of 80 words
    uint8_t i;
    uint32_t W[80];
    for(i = 0;i < 80;i++){
	if(i / 16 == 0)
	    W[i] = M[i];
	else
	    W[i] = RotLeft((W[i-3] ^ W[i-8] ^ W[i-14] ^ W[i-16]), 1);
    }
    //Prepared message schedule
    printf("\nPrepared message schedule : \n");
    for(i = 0;i < 80;i++){
        printf("%08x ",W[i]);
	if(i % 16 == 15 && i > 0)
	    printf("\n");
    }

    uint32_t a,b,c,d,e;
    uint64_t T;
    a = h0;b = h1;c = h2;d = h3;e = h4;
    for(i=0;i < 80; i++){
        T = (uint64_t)RotLeft(a, 5) + (uint64_t)e + (uint64_t )W[i] + (uint64_t)K[i/20];
        switch(i/20){
	    case 0:
   	        T += (uint64_t)Ch(b,c,d);
		break;
	    case 1:
	        T += (uint64_t)Parity(b,c,d);
                break;
	    case 2:
		T += (uint64_t)Maj(b,c,d);
                break;
	    case 3:
		T += (uint64_t)Parity(b,c,d);
                break;
	    default:
		printf("\nError\n");
		break;
	}
        e = d;
	d = c;
	c = RotLeft(b, 30);
	b = a;
	a = (uint32_t)(T & 0xffffffff);
	printf("\nt = %d : ",i);
	printf("%08x  %08x  %08x  %08x  %08x\n",a,b,c,d,e);
    }
    h0 += a;
    h1 += b;
    h2 += c;
    h3 += d;
    h4 += e;
}
uint32_t RotLeft(uint32_t w, uint8_t n){
    return ((w << n) | (w >> (32 - n)));
}
    

