#include<stdio.h>
#include<stdint.h>

#include "md5.h"

int main(int argc, char * argv[]){
    char* input;
    input = argv[1];
    printf("\nGiven input: %s\n",input);
    if(argc > 2)
	printf("\ncan't be done for now\n");
    else{
	md5_main(input);
    }
    return 0;
}

