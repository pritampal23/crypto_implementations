#include "aes.h"

unsigned char key[16] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
unsigned char IV[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
// AES-CBC-128 Mode
void aes_cbc_128(unsigned char *);

int main(int argc, char* argv[]){
    unsigned char plaintext[] = {0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a,0xae,0x2d,0x8a,0x57,0x1e,0x03,0xac,0x9c,0x9e,0xb7,0x6f,0xac,0x45,0xaf,0x8e,0x51,0x30,0xc8,0x1c,0x46,0xa3,0x5c,0xe4,0x11,0xe5,0xfb,0xc1,0x19,0x1a,0x0a,0x52,0xef,0xf6,0x9f,0x24,0x45,0xdf,0x4f,0x9b,0x17,0xad,0x2b,0x41,0x7b,0xe6,0x6c,0x37,0x10};
    aes_cbc_128(plaintext);

    //else
	//printf("\n Error give input\n");
}

void aes_cbc_128(unsigned char *plaintext){
    unsigned char block_message[16];
    unsigned char expandedkey[176];
    uint64_t mlen = strlen(plaintext);
    uint64_t offset = mlen / 16;
    unsigned char ciphertext[16 * (offset+1)];
    unsigned char round_iv[16];
    uint8_t i=0,j,k=0;
    
    for(i=0; i < 16;i++)
        round_iv[i] = IV[i];
    key_expansion(key, expandedkey);
    printf("\nExpanded round key : \n");
    for(i = 0; i< (Nr +1);i++){
        for(j=0;j<16;j++)
	    printf("%2.2x%c",expandedkey[16*i+j], (j != 15)?' ':'\n');
    }

    //Encryption
    printf("\nENRYPTION\n");
    while(k < offset){
	for(j = 0; j < 16; j++)
	    block_message[j] = plaintext[16 * k + j];
        XOR(block_message, round_iv, block_message);

	//Print Input Block
	printf("\nInput block %d : ", k+1);
        for(i = 0;i < 16;i++)
            printf("%2.2x",block_message[i]);
	aes_encrypt(expandedkey, block_message, &ciphertext[k*16]);

	//Print Output Block
	printf("\nciphertext of block %d : ", k+1);
        for(i =0 ;i< 16; i++){
            printf("%2.2x",ciphertext[k*16 + i]);
        }
        for(i = 0;i<16;i++)
	    round_iv[i]= ciphertext[k*16 + i];

	k++;
    }

    //padding
    uint64_t last_block_size = mlen % 16;
    uint64_t padding_len = 16 - last_block_size;
    padding(&plaintext[16 * offset], padding_len, block_message);
    XOR(block_message, round_iv, block_message);
    
    //Print Input Block
    printf("\nInput block %d : ", k+1);
    for(i = 0;i < 16;i++)
        printf("%2.2x",block_message[i]);
    aes_encrypt(expandedkey, block_message, &ciphertext[offset * 16]);
    //Print Output Block
    printf("\nciphertext of block %d : ", k+1);
    for(i =0 ;i< 16; i++){
        printf("%2.2x",ciphertext[16 * offset + i]);
    }

    printf("\n\n");
    //Decryption
    printf("\nDECRYPTION\n");
    k=0;
    for(i=0; i < 16;i++)
	round_iv[i] = IV[i];
    while(k <= offset){
	//Print Input Block
        printf("\nInput block %d : ", k+1);
        for(i = 0;i < 16;i++)
            printf("%2.2x",ciphertext[16*k + i]); 

        aes_decrypt(expandedkey, &ciphertext[k*16], block_message);
	XOR(block_message, round_iv, block_message);
	//Print Output Block
        printf("\nOutput block %d : ", k+1);
        for(i =0 ;i< 16; i++){
            printf("%2.2x",block_message[i]);
        }
        for(i = 0;i<16;i++)
            round_iv[i] = ciphertext[k*16 + i];

        k++;
    }
    printf("\n\n");
}

