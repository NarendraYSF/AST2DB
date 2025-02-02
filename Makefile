CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -Isrc
LDFLAGS = -lclang

TARGET = build/demo
SRC_DIR = src
OBJ_DIR = build/obj
INCLUDE_DIR = include
SRCS = $(wildcard $(SRC_DIR)/*.cc $(SRC_DIR)/ast_analyzer/*.cc $(SRC_DIR)/utils/*.cc)
OBJS = $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(OBJS:.o=.d)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET) tests/moderate-case.cc > tests/output

help:
	@echo "Usage:"
	@echo "  make        # Build"
	@echo "  make run    # Build and run test on moderate-case, redirect output to tests/output"
	@echo "  make clean  # Clean up all build files"
