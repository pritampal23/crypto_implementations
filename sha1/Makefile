CC = gcc

CFLAGS = -c

#SHA1 calculation
SHA1: sha1_input.o sha1.o sha1_padding.o
	$(CC) sha1_input.o sha1.o sha1_padding.o -o sha1
sha1_input.o: sha1_input.c
	$(CC) $(CFLAGS) sha1_input.c
sha1.o: sha1.c
	$(CC) $(CFLAGS) sha1.c
sha1_padding.o: sha1_padding.c
	$(CC) $(CFLAGS) sha1_padding.c

#20 byte HMAC calculation using sha1

HMAC: sha1.o hmac_text.o hmac.o sha1_padding.o
	$(CC) sha1.o hmac_text.o hmac.o sha1_padding.o -o hmac
hmac_text.o: hmac_text.c
	$(CC) $(CFLAGS) hmac_text.c
hmac.o: hmac.c
	$(CC) $(CFLAGS) hmac.c

CLEAN: 
	rm -rf *.o sha1 hmac
