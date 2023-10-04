CC = gcc
CFLAGS = -c

#AES-128 basic implementation
AES-128: aes_main.o aes.o KeyExpansion.o 
	$(CC) aes_main.o aes.o KeyExpansion.o -o aes-128.out
aes_main.o: aes_main.c
	$(CC) $(CFLAGS) aes_main.c
aes.o: aes.c
	$(CC) $(CFLAGS) aes.c
KeyExpansion.o: KeyExpansion.c
	$(CC) $(CFLAGS) KeyExpansion.c

#AES-CBC-128 basic implementation
AES-CBC-128: aes-cbc-128.o aes.o KeyExpansion.o XOR.o padding.o
	$(CC) aes-cbc-128.o aes.o KeyExpansion.o XOR.o padding.o -o aes-cbc-128.out
aes-cbc-128.o: aes-cbc-128.c
	$(CC) $(CFLAGS) aes-cbc-128.c
XOR.o: XOR.c
	$(CC) $(CFLAGS) XOR.c
padding.o: padding.c
	$(CC) $(CFLAGS) padding.c

#AES-CTR-128 basic implementation

AES-CTR-128: aes-ctr-128.o aes.o KeyExpansion.o XOR.o padding.o
	$(CC) aes-ctr-128.o aes.o KeyExpansion.o XOR.o padding.o -o aes-ctr-128.out
aes-ctr-128.o: aes-ctr-128.c
	$(CC) $(CFLAGS) aes-ctr-128.c

#Clean the executables
CLEAN:
	rm -rf *.o *.out


