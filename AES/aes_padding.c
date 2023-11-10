#include "aes.h"

void aes_padding(unsigned char *plaintext,uint64_t padding_len, unsigned char *block_message){
    uint8_t j;
    uint64_t last_block_size = 16 - padding_len;
    for(j = 0; j < 16; j++){
        if(j < last_block_size)
            block_message[j] = plaintext[j];
        else if(j == last_block_size)
            block_message[j] = 0x80;
        else
            block_message[j] = 0x00;
    }
}
