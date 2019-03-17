include ../Make.defines

PROGS = mainpipe fduplex mainpopen mainfifo server_main client_main pipeconf

all:	${PROGS}

mainpipe:	mainpipe.o client.o server.o
	${CC} ${CFLAGS} -o $@ mainpipe.o client.o server.o ${LIBS}

fduplex:	fduplex.o
	${CC} ${CFLAGS} -o $@ fduplex.o ${LIBS}

mainpopen:	mainpopen.o
	${CC} ${CFLAGS} -o $@ mainpopen.o ${LIBS}

mainfifo:	mainfifo.o client.o server.o
	${CC} ${CFLAGS} -o $@ mainfifo.o client.o server.o ${LIBS}

server_main:	server_main.o server.o
	${CC} ${CFLAGS} -o $@ server_main.o server.o ${LIBS}

client_main:	client_main.o client.o 
	${CC} ${CFLAGS} -o $@ client_main.o client.o ${LIBS}

pipeconf:	pipeconf.o
	${CC} ${CFLAGS} -o $@ pipeconf.o ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
