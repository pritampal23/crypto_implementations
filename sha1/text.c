#include "sha1.h"


int main(int argc, unsigned char *argv[]){
    uint32_t hmac[5];
    unsigned char text[] = {0x53,0x61,0x6d,0x70,0x6c,0x65,0x20,0x23,0x31};
    hmac_main(text, hmac);
    printf("\nHMAC : ");
    for(int j=0;j<5;j++)
        printf("%08x ",hmac[j]);
    printf("\n\n");
    /*if(argc > 1){
	for(int i=1; i < argc;i++){
	    hmac_main(argv[i], hmac);
	    printf("\nHMAC %d: ", i+1);
            for(int j=0;j<16;j++)
	        printf("%2.2x",hmac[j]);
        }
    }
    else
	printf("\nError\n");
    */
    return 0;
}
    	    
