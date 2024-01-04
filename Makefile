CFILES = $(wildcard *.c)
OBJS = $(CFILES:.c=.o)

.PHONY: all clean

all: addressBook

# *.o ---> addressBook
addressBook: $(OBJS)
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# *.c ---> *.o
%.o: %.c
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
