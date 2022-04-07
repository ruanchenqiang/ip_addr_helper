CFLAGS=-std=gnu99
EXEC_PROG=ipv6_addr_representation

all: $(EXEC_PROG)

OBJS=main.o

$(EXEC_PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

.PHONY: clean
clean:
	$(RM) $(EXEC_PROG) *.o

