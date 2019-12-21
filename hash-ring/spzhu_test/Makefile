CC = gcc -g
override CFLAGS += -O3 -Wall -fPIC
LDFLAGS = 
#OBJECTS = build/md5_test.o build/md5.o

MD5_SRC = md5.c md5_test.c
SHA1_SRC = sha1.c sha1_test.c

all: md5_test sha1_test

md5_test: ${MD5_SRC}
	@echo Compiling program `basename $@` ...
	@$(CC) ${CFLAGS} ${LDFLAGS} -o $@ ${MD5_SRC} 
	

sha1_test: ${SHA1_SRC}
	@echo Compiling program `basename $@` ...
	@$(CC) ${CFLAGS} ${LDFLAGS} -o $@ ${SHA1_SRC} 

