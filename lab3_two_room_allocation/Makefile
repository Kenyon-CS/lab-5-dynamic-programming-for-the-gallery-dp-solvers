CXX      := g++
CXXFLAGS := -std=c++17 -O2 -g -Wall -Wextra -pedantic

BIN_DIR  := bin
BUILD_DIR:= build
TARGET   := $(BIN_DIR)/lab

SRC      := src/main.cpp
OBJ      := $(BUILD_DIR)/main.o

all: $(TARGET)

$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

$(BUILD_DIR)/main.o: $(SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(BUILD_DIR)/main.o

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)

run: all
	@echo "Usage: ./bin/lab data/simple.txt"
