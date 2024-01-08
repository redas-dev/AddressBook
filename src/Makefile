CFILES := $(wildcard *.c)     # All .c files
OBJS := $(CFILES:.c=.o)       # Tranform the names from *.c -> *.o

.PHONY: all clean

all: $(OBJS)

# *.c ---> *.o
%.o: %.c $(CFILES)
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -f $(OBJS)