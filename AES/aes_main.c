#include "aes.h"

int main(){
    unsigned char plaintext[16] = {'a','b','c','d','e','f','1','2','3','4','5','6','7','8','9','0'};
    unsigned char key[16] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
    unsigned char expandedkey[176];
    unsigned char ciphertext[16];
    unsigned char decryptedtext[16];
    uint8_t i,j;

    //AES KEY Expansion
    key_expansion(key, expandedkey);
    printf("\nExpanded round key : \n");
    for(i = 0; i< (Nr +1);i++){
        for(j=0;j<16;j++)
            printf("%2.2x%c",expandedkey[16*i+j], (j != 15)?' ':'\n');
    }
    
    //Encryption
    printf("\nPlaintext : ");
    for(i = 0;i < 16;i++)
        printf("%2.2x",plaintext[i]);
    aes_encrypt(expandedkey, plaintext, ciphertext);
    printf("\nciphertext : ");
    for(uint8_t i =0 ;i< 16; i++){
        printf("%2.2x",ciphertext[i]);
    }
    //Decryption
    aes_decrypt(expandedkey, ciphertext, decryptedtext);
    printf("\nDecrypted text : ");
    for(uint8_t i =0 ;i< 16; i++){
        printf("%2.2x",decryptedtext[i]);
    }
    printf("\n\n");
    return 0;
}
