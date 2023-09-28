#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include "md5.h"

/*
#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476

#define F(b,c,d) (((b)&(c)) | ((~(b)) & (d)))
#define G(b,c,d) (((b)&(d)) | ((c) & ~(d)))
#define H(b,c,d) ((b) ^ (c) ^ (d))
#define I(b,c,d) ((c) ^ ((b) | (~(d))))
*/

uint8_t k[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
	     1,6,11,0,5,10,15,4,9,14,3,8,13,2,7,12,
	     5,8,11,14,1,4,7,10,13,0,3,6,9,12,15,2,
	     0,7,14,5,12,3,10,1,8,15,6,13,4,11,2,9};


uint8_t S[]={7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,
	     5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
	     4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
	     6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21};

uint32_t T[]={         0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
                       0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
                       0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
                       0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
                       0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
                       0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
                       0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
                       0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
                       0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
                       0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
                       0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
                       0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
                       0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
                       0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                       0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
                       0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
              };
uint32_t AA,BB,CC,DD;
uint64_t m_len;
void md5_main(unsigned char *input){
    m_len = strlen(input);//byte length of the input
    
    uint64_t offset = m_len / 64;
    uint8_t count = 0,i,j=0;
    AA = A; BB = B; CC = C; DD = D;
    while(count < offset){
	uint32_t X[16];
        for(i=0;i< (64/4);i++){
            X[i] = ((uint32_t)input[j]) | ((uint32_t)input[j+1] << 8) | ((uint32_t)input[j+2] << 16) | ((uint32_t)input[j+3] << 24);
	    j = j+4;
        }
	md5_update(X);
	count++;
    }

    //padding
    uint64_t offset2; 
    offset2 = m_len % 64;
    uint64_t padding_len = offset2 < 56 ? 56 - offset2 : (56+64) - offset2;
    md5padding(&input[offset*64],offset2, padding_len);
    

    //Output
    AA = ((AA & 0x000000FF) << 24) | ((AA & 0x0000FF00) << 8) | ((AA & 0x00FF0000) >> 8) | ((AA & 0xFF000000) >> 24);
    BB = ((BB & 0x000000FF) << 24) | ((BB & 0x0000FF00) << 8) | ((BB & 0x00FF0000) >> 8) | ((BB & 0xFF000000) >> 24);
    CC = ((CC & 0x000000FF) << 24) | ((CC & 0x0000FF00) << 8) | ((CC & 0x00FF0000) >> 8) | ((CC & 0xFF000000) >> 24);
    DD = ((DD & 0x000000FF) << 24) | ((DD & 0x0000FF00) << 8) | ((DD & 0x00FF0000) >> 8) | ((DD & 0xFF000000) >> 24);
    printf("\nmessage digest: %08x%08x%08x%08x\n",AA,BB,CC,DD);

}
void md5_update(uint32_t *X){
    uint8_t i,j;
    printf("\nInput:\n");
    for(uint8_t p =0; p < 16;p++)
        printf("%2.2x|",X[p]);
    printf("\n\n");
    uint32_t a=AA,b=BB,c=CC,d=DD;
    for(i = 0; i< 64;i++){
        switch(i/16){
	    case 0:
                R1(X, &a, &b, &c, &d,i);
		//printf("\nmessage digest: %2.2x|%2.2x|%2.2x|%2.2x\n",a,b,c,d);
		break;
	    case 1:
                R2(X, &a, &b, &c, &d,i);
		//printf("\nmessage digest: %2.2x|%2.2x|%2.2x|%2.2x\n",a,b,c,d);
		break;
	    case 2:
                R3(X, &a, &b, &c, &d,i);
		//printf("\nmessage digest: %2.2x|%2.2x|%2.2x|%2.2x\n",a,b,c,d);
		break;
	    case 3:
                R4(X, &a, &b, &c, &d,i);
		//printf("\nmessage digest: %2.2x|%2.2x|%2.2x|%2.2x\n",a,b,c,d);
		break;
	    defailt:
		printf("ERROR....\n");
	}
    }
    AA = a + AA;
    BB = b + BB;
    CC = c + CC;
    DD = d + DD;
    //printf("\nmessage digest: %8.2x|%8.2x|%8.2x|%8.2x\n",AA,BB,CC,DD);
}
void md5padding(unsigned char *msg,uint64_t offset, uint64_t padding_len){
    uint8_t i,j=0;
    uint64_t  len = offset + padding_len;
    unsigned char message[len];
    for(i=0;i<len;i++){
        if(i < offset)
             message[i] = msg[i];
        else if(i == offset && padding_len > 0)
             message[i] = 0x80;
        else
             message[i]=0x00;
    }
    uint32_t X[16];
    uint64_t k = len;
    while(k / 64 > 0){
	for(i=0;i< (64/4);i++){
            X[i] = ((uint32_t)message[j]) | ((uint32_t)message[j+1] << 8) | ((uint32_t)message[j+2] << 16) | ((uint32_t)message[j+3] << 24);
            j = j+4;
        }
        md5_update(X);
	k = k % 64;
    }
    for(i=0;i< (56/4);i++){
        X[i] = ((uint32_t)message[j]) | ((uint32_t)message[j+1] << 8) | ((uint32_t)message[j+2] << 16) | ((uint32_t)message[j+3] << 24);
	j=j+4;
    }
    X[15] = (m_len * 8) >> 32;
    X[14] = (m_len * 8) & (uint32_t)0xffffffff;
    md5_update(X);
}


void R1(uint32_t *X, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d,uint8_t i){
    uint32_t r;
	r = F(*b, *c, *d) + *a + X[k[i]] + T[i];
	r = rotate(r, S[i]);
        r = r + *b;
	*a = *d;
	*d = *c;
	*c = *b;
	*b = r;
    
}
void R2(uint32_t *X, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d,uint8_t i){
    uint32_t r;
    
        r = G(*b, *c, *d) + *a + X[k[i]] + T[i];
        r = rotate(r, S[i]);
        r = r + *b;
        *a = *d;
        *d = *c;
        *c = *b;
        *b = r;
}
void R3(uint32_t *X, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d,uint8_t i){
    uint32_t r;
        r = H(*b, *c, *d) + *a + X[k[i]] + T[i];
        r = rotate(r, S[i]);
        r = r + *b;
        *a = *d;
        *d = *c;
        *c = *b;
        *b = r;
}
void R4(uint32_t *X, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d, uint8_t i){
    uint32_t r;
        r = I(*b, *c, *d) + *a + X[k[i]] + T[i];
        r = rotate(r, S[i]);
        r = r + *b;
        *a = *d;
        *d = *c;
        *c = *b;
        *b = r;
}

