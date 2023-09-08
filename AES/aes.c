#include<stdio.h>
#include<stdint.h>
#include<string.h>

#define Nr 10
#define Nk 4
unsigned char sbox[256] = {
    // 0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,  // 0
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,  // 1
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,  // 2
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,  // 3
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,  // 4
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,  // 5
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,  // 6
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,  // 7
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,  // 8
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,  // 9
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,  // A
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,  // B
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,  // C
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,  // D
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,  // E
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}; // F

unsigned char rsbox[256] =
    {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb, 
     0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, 
     0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, 
     0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, 
     0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, 
     0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84, 
     0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, 
     0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, 
     0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73, 
     0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, 
     0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, 
     0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, 
     0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, 
     0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, 
     0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, 
     0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d};

// Implementation: Rcon
unsigned char Rcon[255] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
    0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
    0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
    0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d,
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab,
    0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d,
    0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25,
    0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01,
    0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d,
    0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa,
    0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a,
    0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02,
    0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
    0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
    0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
    0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
    0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f,
    0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5,
    0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33,
    0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb};

//unsigned char key[16] = {0x67, 0xaf, 0x91, 0xf0, 0xf4, 0xa2, 0x88, 0xbb, 0x11, 0xfc, 0xa9, 0x5b, 0xed, 0xdc, 0x0a, 0x9e};
unsigned char key[16] = {'k', 'k', 'k', 'k', 'e', 'e', 'e', 'e', 'y', 'y', 'y', 'y', '.', '.', '.', '.'};


unsigned char plaintext[16] = {'a','b','c','d','e','f','1','2','3','4','5','6','7','8','9','0'};
unsigned char expandedkey[176];
void key_expansion();
void subword(unsigned char *input);
void rotate_word(unsigned char *input);
void aes_encrypt(unsigned char *state, unsigned char *ciphertext);
void subbytes(unsigned char *state);
void shift_row(unsigned char *state);
void left_shift(unsigned char *row, uint8_t nbr);
void mixcolumn(unsigned char *state);
void ret_column(unsigned char *column);
unsigned char galoi_multiplication(unsigned char a, unsigned char b);
void generate_roundkey(unsigned char* roundkey, uint8_t round);
void Add_roundkey(unsigned char *state, unsigned char *roundkey);

void aes_decrypt(unsigned char *state, unsigned char *ciphertext);
void invsubbytes(unsigned char *state);
void invshift_row(unsigned char *state);
void right_shift(unsigned char *row, uint8_t nbr);
void invmixcolumn(unsigned char *state);
void invret_column(unsigned char *column);

void print(unsigned char *input);
//void Add_roundkey(unsigned char *state, unsigned char *roundkey);


int main(){
    unsigned char ciphertext[16], state[16];
    uint8_t i,j;
    for(i= 0;i < 4;i++)
	for(j =0;j < 4;j++)
            state[4*i+j] = plaintext[4*j + i];
    printf("\nSecret key : ");
    for(i = 0;i < 16;i++)
        printf("%2.2x%c",key[i], (i != 15)?' ':'\n');
    printf("\nPlaintext : ");
    for(i = 0;i < 16;i++)
        printf("%2.2x%c",plaintext[i], (i != 15)?' ':'\n'); 
    //AES Key Expansion
    key_expansion();
    printf("\nExpanded round key : \n");
    for(i = 0; i< (Nr +1);i++){
        for(j=0;j<16;j++)
	    printf("%2.2x%c",expandedkey[16*i+j], (j != 15)?' ':'\n');
    }
    
    //AES Encryption
    aes_encrypt(state, ciphertext);
    printf("\nciphertext : ");
    for(uint8_t i =0 ;i< 16; i++){
	printf("%2.2x%c",ciphertext[i], (i != 15)?' ':'\n');
    }
   
    //AES Decryption
    unsigned char DecryptedText[16];
    for(i= 0;i < 4;i++)
        for(j =0;j < 4;j++)
            state[4*i+j] = ciphertext[4*j + i]; 
    aes_decrypt(state, DecryptedText);
    printf("\nDecryptedText : ");
    for(uint8_t i =0 ;i< 16; i++){
        printf("%2.2x%c",DecryptedText[i], (i != 15)?' ':'\n');
    }
    
    return 0;
}
void key_expansion(){
    uint8_t i =0,j;
    unsigned char tmp1[4], tmp2[4];
    for(;i < 4; i++)
	for(j = 0;j<4;j++)
	   expandedkey[4*i+j] = key[4*i+j];
    for(;i < 4*(Nr+1); i++){
	for(j = 0;j< 4;j++){
	    tmp1[j] = expandedkey[4*(i-1) +j];
	    tmp2[j] = expandedkey[4*(i - Nk) +j];
	}
	if(i % Nk == 0){
	    rotate_word(tmp1);
	    subword(tmp1);
	    tmp1[0] = tmp1[0] ^ Rcon[i/Nk];
	}
	for(j =0 ;j <4 ;j++)
            expandedkey[4*i +j] = tmp2[j] ^ tmp1[j];
    }
}
void subword(unsigned char *input){
   
    for(uint8_t i=0; i<4;i++)
	input[i] = sbox[input[i]];
    
}
void rotate_word(unsigned char *input){
    unsigned char left;
    uint8_t i =0;
    left = input[0];
    for(;i<3;i++)
	input[i] = input[i+1];
    input[i] =left;
  
}
void aes_encrypt(unsigned char *state, unsigned char *ciphertext){
    unsigned char roundkey[16];
    //print(state);
    //printf("\nRound 0:\n"); 
    generate_roundkey(roundkey, 0);
    Add_roundkey(state, roundkey);
    //print(state);
    for(int i=1;i<Nr;i++){
	//printf("\nRound %d:\n",i);
        subbytes(state);
        //print(state);
        shift_row(state);
	//print(state);
        mixcolumn(state);
	//print(state);
	generate_roundkey(roundkey, i);
        Add_roundkey(state, roundkey);
	//print(state);
    }
    //printf("\nRound 10:\n");
    subbytes(state);
    //print(state);
    shift_row(state);
    //print(state);
    generate_roundkey(roundkey, 10);
    Add_roundkey(state, roundkey);    

    for(uint8_t i =0 ;i<4; i++){
	for(uint8_t j=0; j<4; j++)
            ciphertext[4*i+j] = state[4*j+i];
    }

}
void generate_roundkey(unsigned char* roundkey, uint8_t round){
    for(uint8_t i = 0;i < 16; i++)
	roundkey[i] = expandedkey[16 * round + i];
}
void subbytes(unsigned char *state){
    
    for(uint8_t i=0;i<16;i++)
	state[i] = sbox[state[i]];
    
}

void shift_row(unsigned char  *state){
    for(uint8_t i =0; i<4;i++)
	left_shift(state + i*4, i);
}
void left_shift(unsigned char *row, uint8_t nbr){
    unsigned char left;
    for(uint8_t i = 0;i< nbr; i++){
	left = row[0];
	for(uint8_t j=0;j<3;j++)    
	    row[j] = row[j+1];
	row[3] = left;
    }
}
void mixcolumn(unsigned char *state){
    unsigned char column[4];
    for(uint8_t i=0; i< 4;i++){
	for(uint8_t j=0; j <4;j++)
	    column[j] = state[(j * 4)+i];
	ret_column(column);
        for(uint8_t j = 0;j < 4;j++)
            state[(j * 4)+i] = column[j];
   }
}
void ret_column(unsigned char *column){
    unsigned char copy[4];
    for(uint8_t i = 0;i < 4;i++)
	copy[i] = column[i];
    column[0] = galoi_multiplication(0x02, copy[0]) ^ galoi_multiplication(0x03, copy[1]) ^ galoi_multiplication(0x01, copy[2]) ^ galoi_multiplication(0x01, copy[3]);
    column[1] = galoi_multiplication(0x01, copy[0]) ^ galoi_multiplication(0x02, copy[1]) ^ galoi_multiplication(0x03, copy[2]) ^ galoi_multiplication(0x01, copy[3]);
    column[2] = galoi_multiplication(0x01, copy[0]) ^ galoi_multiplication(0x01, copy[1]) ^ galoi_multiplication(0x02, copy[2]) ^ galoi_multiplication(0x03, copy[3]);
    column[3] = galoi_multiplication(0x03, copy[0]) ^ galoi_multiplication(0x01, copy[1]) ^ galoi_multiplication(0x01, copy[2]) ^ galoi_multiplication(0x02, copy[3]);
}

unsigned char galoi_multiplication(unsigned char a, unsigned char b){
    unsigned char p = 0x00;
    unsigned char bit7;
    for(uint8_t i = 0;i < 8;i++){
	if((b & 1) == 1)
	    p ^= a;
	bit7 = (a & 0x80);
	a <<= 1;
	if(bit7 == 0x80)
	    a ^= 0x1b;
	b >>= 1;
    }
    return p;

}
/*void generate_roundkey(unsigned char* roundkey){
    unsigned char prev_roundkey[16];
    for(uint8_t i = 0; i < 16;i++)
	prev_roundkey[i] = roundkey[i];
    
}*/
void Add_roundkey(unsigned char *state, unsigned char *roundkey){
    
    for(uint8_t i = 0;i < 4;i++)
	for(uint8_t j = 0; j < 4; j++)
	    state[4 *i+j] = state[4*i + j]^ roundkey[4*j + i];
}


// AES decryption
void aes_decrypt(unsigned char *state, unsigned char *DecryptedText){
    unsigned char roundkey[16];
    //printf("\nRound 0: \n");
    generate_roundkey(roundkey, 10);
    Add_roundkey(state, roundkey);
    //print(state);
    for(uint8_t i= Nr - 1;i > 0;i--){
	//printf("\nRound %d:\n", Nr-i);
        invshift_row(state);
	//print(state);
	invsubbytes(state);
	//print(state);
	generate_roundkey(roundkey, i);
        Add_roundkey(state, roundkey);
	//print(state);
	invmixcolumn(state);
	//print(state);
    }
    //printf("\nRound 10:\n");
    invshift_row(state);
    //print(state);
    invsubbytes(state);
    //print(state);
    generate_roundkey(roundkey, 0);
    Add_roundkey(state, roundkey);
    for(uint8_t i =0 ;i< 4; i++){
	for(uint8_t j=0;j<4;j++)
            DecryptedText[4*i+j] = state[4*j+i];
    }

}
void invsubbytes(unsigned char *state){

    for(uint8_t i=0;i<16;i++)
        state[i] = rsbox[state[i]];

}
void invshift_row(unsigned char  *state){
    for(uint8_t i =0; i<4;i++)
        right_shift(state + i*4, i);
}
void right_shift(unsigned char *row, uint8_t nbr){
    unsigned char right;
    for(uint8_t i = 0;i< nbr; i++){
        right = row[3];
        for(uint8_t j=3;j>0;j--)
            row[j] = row[j-1];
        row[0] = right;
    }
}
void invmixcolumn(unsigned char *state){
    unsigned char column[4];
    for(uint8_t i=0; i< 4;i++){
        for(uint8_t j=0; j <4;j++)
            column[j] = state[(j * 4)+i];
        invret_column(column);
        for(uint8_t j = 0;j < 4;j++)
            state[(j * 4)+i] = column[j];
   }
}
void invret_column(unsigned char *column){
    unsigned char copy[4];
    for(uint8_t i = 0;i < 4;i++)
        copy[i] = column[i];
    column[0] = galoi_multiplication(0x0e, copy[0]) ^ galoi_multiplication(0x0b, copy[1]) ^ galoi_multiplication(0x0d, copy[2]) ^ galoi_multiplication(0x09, copy[3]);
    column[1] = galoi_multiplication(0x09, copy[0]) ^ galoi_multiplication(0x0e, copy[1]) ^ galoi_multiplication(0x0b, copy[2]) ^ galoi_multiplication(0x0d, copy[3]);
    column[2] = galoi_multiplication(0x0d, copy[0]) ^ galoi_multiplication(0x09, copy[1]) ^ galoi_multiplication(0x0e, copy[2]) ^ galoi_multiplication(0x0b, copy[3]);
    column[3] = galoi_multiplication(0x0b, copy[0]) ^ galoi_multiplication(0x0d, copy[1]) ^ galoi_multiplication(0x09, copy[2]) ^ galoi_multiplication(0x0e, copy[3]);
}


void print (unsigned char *state){
    printf("\nState : ");
    for(uint8_t i =0 ;i< 16; i++){
        printf("%2.2x%c",state[i], (i != 15)?' ':'\n');
    }
}
