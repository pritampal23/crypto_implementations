#include "aes.h"

unsigned char key[16] = {'k', 'k', 'k', 'k', 'e', 'e', 'e', 'e', 'y', 'y', 'y', 'y', '.', '.', '.', '.'};
unsigned char IV[16] = {'0','0','1','1','2','2','3','3','4','4','5','5','6','6','7','7'};
// AES-CBC-128 Mode
void aes_cbc_128(unsigned char *);
void XOR(unsigned char *A, unsigned char *B);


int main(int argc, char* argv[]){
    if(argc > 1)
	aes_cbc_128(argv[1]);

    else
	printf("\n Error give input\n");
}

void aes_cbc_128(unsigned char *plaintext){
    unsigned char block_message[16];
    unsigned char expandedkey[176];
    unsigned char ciphertext[16];
    uint64_t mlen = strlen(plaintext);
    uint64_t offset = mlen / 16;
    uint8_t i=0,j,k=0;
    
    key_expansion(key, expandedkey);
    printf("\nExpanded round key : \n");
    for(i = 0; i< (Nr +1);i++){
        for(j=0;j<16;j++)
	    printf("%2.2x%c",expandedkey[16*i+j], (j != 15)?' ':'\n');
    }
    while(k < offset){
	for(j = 0; j < 16; j++)
	    block_message[j] = plaintext[16 * k + j];

	/*key_expansion(key, expandedkey);
        printf("\nExpanded round key : \n");
        for(i = 0; i< (Nr +1);i++){
            for(j=0;j<16;j++)
                printf("%2.2x%c",expandedkey[16*i+j], (j != 15)?' ':'\n');
        }*/
        XOR(block_message, IV);
	aes_encrypt(key, block_message, expandedkey, ciphertext);
	printf("\nciphertext of block %d : ", k+1);
        for(i =0 ;i< 16; i++){
            printf("%2.2x%c",ciphertext[i], (i != 15)?' ':'\n');
        }
        for(i = 0;i<16;i++)
	    IV[i]= ciphertext[i];

	k++;
    }
    uint64_t last_block_size = mlen % 16;
    uint64_t padding_len = 16 - last_block_size;
    for(j = 0; j < 16; j++){
	if(j < last_block_size)
	    block_message[j] = plaintext[16 * offset + j];
	else if(j == last_block_size)
	    block_message[j] = 0x80;
	else
	    block_message[j] = 0x00;
    }
    XOR(block_message, IV);
    aes_encrypt(key, block_message, expandedkey, ciphertext);
    printf("\nciphertext of block %d : ", k+1);
    for(i =0 ;i< 16; i++){
        printf("%2.2x%c",ciphertext[i], (i != 15)?' ':'\n');
    }
}

void XOR(unsigned char *A, unsigned char *B){
    for(uint8_t i=0; i< 16; i++)
	A[i] = A[i] ^ B[i];
}
