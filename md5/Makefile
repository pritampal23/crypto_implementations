CC = gcc
CFLAGS = -c

MD5: main.o md5.o
	$(CC)  main.o md5.o -o md5
main.o: main.c
	$(CC) $(CFLAGS) main.c
md5.o: md5.c
	$(CC) $(CFLAGS) md5.c

#Clean the executables

CLEAN: 
	rm -rf *.o md5
