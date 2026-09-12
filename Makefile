CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread -I./src -I./tests -mconsole

SRC_DIR = src
TEST_DIR = tests
BIN_DIR = bin

# ============================================================
# Fichiers source principaux
# ============================================================
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRCS))
TARGET = can_bus_simulator

# ============================================================
# Fichiers de test (TOUS les .cpp dans tests/)
# ============================================================
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(BIN_DIR)/%.o,$(TEST_SRCS))
TEST_TARGET = can_bus_tests

# ============================================================
# Compilation
# ============================================================
all: clean $(TARGET).exe $(TEST_TARGET).exe

$(BIN_DIR):
	mkdir $(BIN_DIR)

# Programme principal
$(TARGET).exe: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lstdc++fs

# Objets dans bin/
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ============================================================
# Tests : compile TOUS les fichiers de test + unity.c
# ============================================================
$(TEST_TARGET).exe: $(TEST_OBJS) $(BIN_DIR)/can_bus.o $(BIN_DIR)/can_message.o $(BIN_DIR)/can_logger.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ $(TEST_DIR)/unity.c -o $@ -lstdc++fs

# Objets des tests dans bin/
$(BIN_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ============================================================
# Nettoyage
# ============================================================
clean:
	-del /Q $(BIN_DIR)\*.o 2>nul
	-rmdir $(BIN_DIR) 2>nul
	-del /Q *.exe 2>nul
	-rmdir /s /q log 2>nul

.PHONY: all clean