#CC=arm-linux-gnueabihf-gcc
#CXX=arm-linux-gnueabihf-g++
CC ?= gcc
CXX ?= g++
IFLAGS = -I$(SRC_DIR) -I$(SRC_DIR)/peripherals
CPPFLAGS = -g -Wall -MD -MP $(IFLAGS) -O
LDFLAGS = -lpthread

SRC_DIR     = src
BIN_DIR     = bin
BUILD_DIR   = $(BIN_DIR)/build

SOURCES := $(wildcard $(SRC_DIR)/*.c)
SOURCES += $(wildcard $(SRC_DIR)/peripherals/*.c)
SOURCES := $(SOURCES:$(SRC_DIR)/%=%)
OBJECTS = $(SOURCES:%.c=$(BUILD_DIR)/%.o)

all: passthrough_linux

passthrough_linux: $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o:$(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) -c $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/peripherals

clean:
	rm -rf $(BIN_DIR)
	rm -f passthrough_linux

-include $(OBJECTS:.o=.d)
