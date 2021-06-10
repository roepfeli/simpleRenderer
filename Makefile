CC = g++
LD = g++

CFLAGS = -Wall -g
CXXFLAGS = $(CFLAGS) -std=gnu++17
INCLUDE = -I./include/ -I./lib/include/
LFLAGS = -lGL -lGLEW -lglfw -lm
DEBUG_FLAGS = -ggdb
SRC_DIR = src
OBJ_DIR = build
PROG_NAME = simpleRender.elf


SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o , $(SOURCES))

build: $(OBJECTS)
	$(LD) $^ -o $(PROG_NAME) $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(INCLUDE) $(DEBUG_FLAGS) -c $< $(CXXFLAGS) -o $@

.PHONY: clean build

clean:
	rm -rf $(OBJ_DIR)/*
	rm *.elf