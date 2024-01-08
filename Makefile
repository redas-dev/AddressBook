SRC_DIR := src
LIB_DIR := lib
TARGET := addressBook

.PHONY: all clean

all: compile_src install_lib $(TARGET)

compile_src:
	make -C $(SRC_DIR)

install_lib:
	make -C $(LIB_DIR)

$(TARGET): $(wildcard $(SRC_DIR)/*.o)
	@echo $<
	@echo $@

clean:
	rm -f $(PROGRAM)
	make clean -C $(SRC_DIR)
	make clean -C $(LIB_DIR)