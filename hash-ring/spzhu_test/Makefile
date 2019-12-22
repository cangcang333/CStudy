CC = gcc -g
override CFLAGS += -O3 -Wall -fPIC
LDFLAGS = 
OBJECTS = build/sha1.o build/md5.o build/hash_ring.o build/sort.o
TEST_OBJECTS = build/hash_ring_test3.o

MD5_SRC = md5.c md5_test.c
SHA1_SRC = sha1_test.c
HASH_RING_SRC = hash_ring_test3.c

SHARED_LIB = build/libhashring.so

EXECFILE = md5_test sha1_test hash_ring_test3

all: ${EXECFILE}

md5_test: ${MD5_SRC}
	@echo Compiling program `basename $@` ...
	@$(CC) ${CFLAGS} ${LDFLAGS} -o $@ ${MD5_SRC} 
	

lib: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(SHARED_LIB) -shared

sha1_test: ${SHA1_SRC}
	@echo Compiling program `basename $@` ...
	@$(CC) ${CFLAGS} ${LDFLAGS} ${OBJECTS} -o $@ ${SHA1_SRC}

hash_ring_test3: ${HASH_RING_SRC}
	@echo Compiling program `basename $@` ...
	@$(CC) ${CFLAGS} ${LDFLAGS} ${OBJECTS} -o $@ ${HASH_RING_SRC} 


build/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJECTS) $(TEST_OBJECTS) $(SHARED_LIB)
	rm -rf $(EXECFILE)
