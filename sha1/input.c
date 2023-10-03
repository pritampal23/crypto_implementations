#include "sha1.h"

int main(int argc, char * argv[]){
    unsigned char hash[20];
    
    if(argc > 1){
	for(int i=1;i<argc;i++){
            printf("\ninput %d: %s", i, argv[i]);
	    sha1(argv[i], hash);
	    //printf("\nHash %d: ",i);
	    //for(int j=0;j< 16;j++)
		//printf("%2.2x",hash[j]);
	}
    }
    else
	printf("\nError");
    printf("\n\n");
    return 0;
}

