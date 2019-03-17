include ../Make.defines

PROGS = mainserver mainclient

all:	${PROGS}

mainserver:	mainserver.o
	${CC} ${CFLAGS} -o $@ mainserver.o ${LIBS}

mainclient: mainclient.o	
	${CC} ${CFLAGS} -o $@ mainclient.o ${LIBS}

clean:
	rm -f ${PROGS} ${CLEANFILES}
