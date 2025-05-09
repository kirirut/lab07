CC = gcc
CFLAGS = -W -Wall -Wextra -std=c11
SRC_DIR = src
BUILD_DIR = build

.PHONY: all clean

all: $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR)
