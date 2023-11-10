CC = gcc
CFLAGS = -c

MD5: md5_input.o md5.o
	$(CC)  md5_input.o md5.o -o md5
md5_input.o: md5_input.c
	$(CC) $(CFLAGS) md5_input.c
md5.o: md5.c
	$(CC) $(CFLAGS) md5.c

#Clean the executables

CLEAN: 
	rm -rf *.o md5
