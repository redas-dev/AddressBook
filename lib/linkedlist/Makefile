CFILES := $(wildcard *.c)
OBJS := $(CFILES:.c=.o)

CFLAGS := -Wall -Werror -fPIC
TARGET := liblinkedlist

.PHONY: all clean

all: $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	@$(CC) -shared -o $@.so $(OBJS)

%.o: %.c
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -f $(TARGET).so
