#include "sha1.h"

//HMAC constants
#define ipad 0x36
#define opad 0x5c
void hmac_main(unsigned char *text, uint32_t *hmac){
    uint8_t i;
    unsigned char key[64] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
	                     0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
			     0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
			     0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f};
    printf("\nKey: \n");
    for(i = 0;i < 64;i++)
	printf("%02x%c",key[i],(i % 16 == 15) ? '\n' : ' ');

    //(key ^ ipad)
    unsigned char k1[64];
    for(i = 0;i < 64; i++)
	k1[i] = key[i] ^ ipad;
    printf("\n(key ^ ipad) : \n");
    for(i = 0;i < 64;i++)
        printf("%02x%c",k1[i],(i % 16 == 15) ? '\n' : ' ');
   
    //(key ^ ipad) || text
    uint64_t text_len = strlen(text);
    unsigned char text1[text_len + 64];
    for(i = 0; i < 64; i++)
	text1[i] = k1[i];
    for(i=0;i<text_len;i++)
	text1[64+i] = text[i];
    printf("\n(key ^ ipad) || text : \n");
    for(i = 0;i < (text_len + 64);i++)
        printf("%02x%c",text1[i],(i % 16 == 15) ? '\n' : ' ');
     
    //sha1((key ^ ipad) || text)
    uint32_t hash1[5];
    sha1(text1, hash1, text_len+64);
    printf("\nsha1((key ^ ipad) || text) : \n");
    for(i = 0; i<5;i++)
	printf("%08x ",hash1[i]);

    //(key ^ opad)
    unsigned char k2[64];
    for(i = 0;i < 64; i++)
        k2[i] = key[i] ^ opad;
    printf("\n(key ^ opad) : \n");
    for(i = 0;i < 64;i++)
        printf("%02x%c",k2[i],(i % 16 == 15) ? '\n' : ' ');

    //(key ^ opad) || sha1((key ^ ipad) || text)
    unsigned char text2[84];
    for(i=0;i<64;i++)
	    text2[i] = k2[i];
    text2[i++] = (unsigned char)((hash1[0] >> 24) & 0xff);
    text2[i++] = (unsigned char)((hash1[0] >> 16) & 0xff);
    text2[i++] = (unsigned char)((hash1[0] >> 8) & 0xff);
    text2[i++] = (unsigned char)((hash1[0]) & 0xff);

    text2[i++] = (unsigned char)((hash1[1] >> 24) & 0xff);
    text2[i++] = (unsigned char)((hash1[1] >> 16) & 0xff);
    text2[i++] = (unsigned char)((hash1[1] >> 8) & 0xff);
    text2[i++] = (unsigned char)((hash1[1]) & 0xff);

    text2[i++] = (unsigned char)((hash1[2] >> 24) & 0xff);
    text2[i++] = (unsigned char)((hash1[2] >> 16) & 0xff);
    text2[i++] = (unsigned char)((hash1[2] >> 8) & 0xff);
    text2[i++] = (unsigned char)((hash1[2]) & 0xff);

    text2[i++] = (unsigned char)((hash1[3] >> 24) & 0xff);
    text2[i++] = (unsigned char)((hash1[3] >> 16) & 0xff);
    text2[i++] = (unsigned char)((hash1[3] >> 8) & 0xff);
    text2[i++] = (unsigned char)((hash1[3]) & 0xff);

    text2[i++] = (unsigned char)((hash1[4] >> 24) & 0xff);
    text2[i++] = (unsigned char)((hash1[4] >> 16) & 0xff);
    text2[i++] = (unsigned char)((hash1[4] >> 8) & 0xff);
    text2[i++] = (unsigned char)((hash1[4]) & 0xff);
     
    printf("\n(key ^ ipad) || sha1((key ^ ipad) || text) : \n");
    for(i = 0;i < 84;i++)
        printf("%02x%c",text2[i],(i % 16 == 15) ? '\n' : ' ');

    //sha1((key ^ opad) || sha1((key ^ ipad) || text)
    sha1(text2, hmac, 84);

}
