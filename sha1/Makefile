CC = gcc

CFLAGS = -c

#SHA1 calculation
SHA1: input.o sha1.o padding.o
	$(CC) input.o sha1.o padding.o -o sha1
input.o: input.c
	$(CC) $(CFLAGS) input.c
sha1.o: sha1.c
	$(CC) $(CFLAGS) sha1.c
padding.o: padding.c
	$(CC) $(CFLAGS) padding.c

#20 byte HMAC calculation using sha1

HMAC: sha1.o text.o hmac.o padding.o
	$(CC) sha1.o text.o hmac.o padding.o -o hmac
text.o: text.c
	$(CC) $(CFLAGS) text.c
hmac.o: hmac.c
	$(CC) $(CFLAGS) hmac.c

CLEAN: 
	rm -rf *.o sha1 hmac
