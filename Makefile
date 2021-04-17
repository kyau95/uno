CXXFLAGS := -g -std=c++17 -Werror -Wpedantic
CXX := g++
RM := rm

.PHONY: $(BIN)
.PHONY: clean

VPATH:= ./src/ ./obj/

# Path for .c , .h and .o Files
SRC_PATH := ./src/
OBJ_PATH := ./obj/

# Executable Name
BIN := uno

# Files to compile
_OBJ := main.o \
				deck.o \
				card.o \
				game.o \
				player.o

OBJ := $(patsubst %,$(OBJ_PATH)%,$(_OBJ))

# Build .o first
$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@echo [CXX] $<
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

# Build final Binary
$(BIN): $(OBJ)
	@echo [INFO] Creating Binary Executable [$(BIN)]
	@$(CXX) -o $@ $^

clean:
	rm -f $(OBJ_PATH)*.o
