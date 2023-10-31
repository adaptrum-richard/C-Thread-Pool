BINDIR = /usr/bin

LDFLAGS += -Wl,-export-dynamic

TARGET=pthread_test

OBJS=pthread_test.o thpool.o

LDLIB=-lpthread


all:  ${TARGET}

${TARGET}: ${OBJS}
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o  $@ $(LDLIB)

install: all uninstall
	-mkdir -p $(BINDIR)
	cp ${TARGET} $(BINDIR)

uninstall:
	rm -f $(BINDIR)/${TARGET}
clean:
	rm -rf *.o *~ .*sw*  ${TARGET}