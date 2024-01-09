CFILES := $(wildcard *.c)
OBJS := $(CFILES:.c=.o)

BIN := ../bin

TARGET := addressBook
LIBS := linkedlist

CFLAGS := -I$(HOME)/AddressBookTask/lib/linkedlist -L$(HOME)/AddressBookTask/lib/linkedlist -Wl,-rpath=$(HOME)/AddressBookTask/lib/linkedlist -Wall -Werror

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $(BIN)/$(TARGET) $(OBJS) $(LIBS:%=-l%)

clean:
	@rm -f $(OBJS)