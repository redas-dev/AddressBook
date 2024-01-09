SRC_DIR := src
LIB_DIR := lib
BIN_DIR := bin

TARGET := addressBook

.PHONY: all clean

all: compile_lib compile_src

compile_lib:
	@make -C $(LIB_DIR)/linkedlist

compile_src: $(BIN)
	@make -C $(SRC_DIR)

$(BIN):
	@mkdir $(BIN)

clean:
	@rm -f bin/$(TARGET)
	@make clean -C $(SRC_DIR)
	@make clean -C $(LIB_DIR)/linkedlist