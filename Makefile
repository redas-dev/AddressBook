CFILES := $(wildcard *.c)     # All .c files
OBJS := $(CFILES:.c=.o)       # Tranform the names from *.c -> *.o
PROGRAM := addressBook
CFLAGS += -Wall -Wextra

.PHONY: all clean

all: $(PROGRAM)

# *.o ---> PROGRAM
$(PROGRAM): $(OBJS)
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# *.c ---> *.o
%.o: %.c
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

# Removes all .o files
clean:
	rm -f $(PROGRAM) $(OBJS)