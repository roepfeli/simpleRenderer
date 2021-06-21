CXX 	  		?= g++
LD 				:= $(CXX)
TARGET 			:= simplerender.elf
CXXFLAGS 		:= -Wall -Wextra
BUILD 			:= ./build
OBJ_DIR 		:= $(BUILD)/objects
APP_DIR 		:= $(BUILD)
SRC 			:= $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) # if subfolder exist in src
OBJECTS			:= $(SRC:%.cpp=$(OBJ_DIR)/%.o)

# add external libs and flags
CXXFLAGS 		+= -I/usr/include $(VERSION_FLAGS)
LDFLAGS 		:= -L/usr/lib -lstdc++ -lm
LDFLAGS			+= $(addprefix -L, $(wildcard lib/*/build/objects))
LDLIBS			:= -lGL -lGLEW -lglfw -lm
INCLUDE  		:= -Iinclude/
INCLUDE			+= $(addprefix -I, $(wildcard lib/*/include/))

all: build $(APP_DIR)/$(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(LD) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDLIBS)

valgrind: all
	valgrind \
		--leak-check=full \
		--trace-children=yes \
		--show-leak-kinds=all \
		--track-origins=yes \
		--log-file=./build/valgrind-out.txt \
		./build/$(TARGET)

debug: CXXFLAGS += -DDEBUG -g -v
debug: clean build $(APP_DIR)/$(TARGET)

release: CXXFLAGS += -O2
release: clean all
	-@strip $(BUILD)/$(TARGET)

.PHONY: all build clean debug release valgrind install

clean:
	-@rm -rvf $(BUILD)/$(TARGET)
	-@rm -rvf $(OBJ_DIR)/*
