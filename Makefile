CFILES := $(wildcard *.c)     # All .c files
OBJS := $(CFILES:.c=.o)       # Tranform the names from *.c -> *.o

.PHONY: all clean

all: addressBook

# *.o ---> addressBook
addressBook: $(OBJS)
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# *.c ---> *.o
%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

# Removes all .o files
clean:
	rm -f $(OBJS)