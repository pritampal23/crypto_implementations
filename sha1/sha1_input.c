#include "sha1.h"

int main(int argc,unsigned char *argv[]){
    uint32_t hash[5];
    
    if(argc > 1){
	for(int i=1;i<argc;i++){
            printf("\ninput %d: %s", i, argv[i]);
	    sha1(argv[i], hash, strlen((char *)argv[i]));
	    printf("\nHash: ");
	    for(int j=0;j< 5;j++)
		printf("%08x ",hash[j]);
	    printf("\n");
	}
    }
    else
	printf("\nError");
    printf("\n\n");
    return 0;
}

