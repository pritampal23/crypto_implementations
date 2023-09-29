#include "aes.h"

int main(){
    unsigned char plaintext[16] = {'a','b','c','d','e','f','1','2','3','4','5','6','7','8','9','0'};
    unsigned char key[16] = {'k', 'k', 'k', 'k', 'e', 'e', 'e', 'e', 'y', 'y', 'y', 'y', '.', '.', '.', '.'};
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
    //aes_main(key, plaintext, expandedkey);
    //Encryption
    aes_encrypt(key, plaintext, expandedkey, ciphertext);
    printf("\nciphertext : ");
    for(uint8_t i =0 ;i< 16; i++){
        printf("%2.2x%c",ciphertext[i], (i != 15)?' ':'\n');
    }
    //Decryption
    aes_decrypt(key, expandedkey, ciphertext, decryptedtext);
    printf("\nDecrypted text : ");
    for(uint8_t i =0 ;i< 16; i++){
        printf("%2.2x%c",decryptedtext[i], (i != 15)?' ':'\n');
    }

    return 0;
}
