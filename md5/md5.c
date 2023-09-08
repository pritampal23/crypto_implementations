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

void md5_main(unsigned char *input){
    uint64_t m_len = 288;
    unsigned char message[56]={'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m','1','2','3','4','5','6','7','8','9','0',0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    
    uint32_t X[16];
    uint8_t i,j;
    for(i=0;i< (56/4);i++){
	j = 4*i;
	X[i] = ((uint32_t)message[j]) | ((uint32_t)message[j+1] << 8) | ((uint32_t)message[j+2] << 16) | ((uint32_t)message[j+3] << 24);
    }
    X[15] = m_len >> 32;
    X[14] = m_len & (4294967295);
    printf("\nInput:\n");
    for(uint8_t p =0; p < 16;p++)
	printf("%2.2x|",X[p]);
    printf("\n\n");
    uint32_t a=A,b=B,c=C,d=D;
    //for(i=0;i < N/16 - 1;i++){
        R1(X, &a, &b, &c, &d);
        R2(X, &a, &b, &c, &d);
        R3(X, &a, &b, &c, &d);
        R4(X, &a, &b, &c, &d);
        a = A + a;
        b = B + b;
        c = C + c;
        d = D + d;
    //}

    a = ((a & 0x000000FF) << 24) | ((a & 0x0000FF00) << 8) | ((a & 0x00FF0000) >> 8) | ((a & 0xFF000000) >> 24);
    b = ((b & 0x000000FF) << 24) | ((b & 0x0000FF00) << 8) | ((b & 0x00FF0000) >> 8) | ((b & 0xFF000000) >> 24);
    c = ((c & 0x000000FF) << 24) | ((c & 0x0000FF00) << 8) | ((c & 0x00FF0000) >> 8) | ((c & 0xFF000000) >> 24);
    d = ((d & 0x000000FF) << 24) | ((d & 0x0000FF00) << 8) | ((d & 0x00FF0000) >> 8) | ((d & 0xFF000000) >> 24);
    printf("\nmessage digest: %2.2x%2.2x%2.2x%2.2x\n",a,b,c,d);

}


/*uint32_t F(uint32_t b,uint32_t c, uint32_t d){
    uint32_t f;
    f = (b&c) | ((~b) & c);
    return f;
}*/

void R1(uint32_t *X, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d){
    uint32_t r;
    uint8_t i,j;

    for(i = 0;i < 16;i++){
	r = F(*b, *c, *d) + *a + X[k[i]] + T[i];
	r = rotate(r, S[i]);
        r = r + *b;
	*a = *d;
	*d = *c;
	*c = *b;
	*b = r;
	
    }
}
void R2(uint32_t *X, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d){
    uint32_t r;
    uint8_t i,j;
    
    for(i = 0;i < 16;i++){
        r = G(*b, *c, *d) + *a + X[k[i+16]] + T[i+16];
        r = rotate(r, S[i+16]);
        r = r + *b;
        *a = *d;
        *d = *c;
        *c = *b;
        *b = r;
	
    }   
}
void R3(uint32_t *X, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d){
    uint32_t r;
    uint8_t i,j;
    
    for(i = 0;i < 16;i++){
        r = H(*b, *c, *d) + *a + X[k[i+32]] + T[i+32];
        r = rotate(r, S[i+32]);
        r = r + *b;
        *a = *d;
        *d = *c;
        *c = *b;
        *b = r;

        
    }   
}
void R4(uint32_t *X, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d){
    uint32_t r;
    uint8_t i,j;

    for(i = 0;i < 16;i++){
        r = I(*b, *c, *d) + *a + X[k[i+48]] + T[i+48];
        r = rotate(r, S[i+48]);
        r = r + *b;
        *a = *d;
        *d = *c;
        *c = *b;
        *b = r;
    }   
}

