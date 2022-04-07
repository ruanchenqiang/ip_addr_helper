CFLAGS=-std=gnu99
EXEC_PROG=ip_addr_category

all: $(EXEC_PROG)

OBJS=main.o

$(EXEC_PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

.PHONY: clean
clean:
	$(RM) $(EXEC_PROG) *.o

