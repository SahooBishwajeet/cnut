# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -Iheaders/

# Linker flags
LDFLAGS = -lm

# Directories
SRC_DIR = src
INC_DIR = headers
BUILD_DIR = build

# Source and Object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Target executable
TARGET = cnut

# Installation prefix
PREFIX = /usr/local

# Build all targets
all: $(TARGET)

# Link object files to create the target executable
$(TARGET): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and target executable
clean:
	@rm -rf $(BUILD_DIR) $(TARGET)

# Install the target executable
install: $(TARGET)
	@install -Dm755 $(TARGET) $(PREFIX)/bin/$(TARGET)

# Uninstall the target executable
uninstall:
	@rm -f $(PREFIX)/bin/$(TARGET)