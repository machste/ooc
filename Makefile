CC = gcc
C_FLAGS = -I./src/include -DLOG_ENABLED -g -O0

# Put all auto generated stuff to this build dir.
BUILD_DIR = ./build

# List of *.c source of all object files.
C_OBJ_FILES = $(wildcard src/util/*.c) $(wildcard src/*.c)
# All .o files go to build dir.
OBJS = $(C_OBJ_FILES:%.c=$(BUILD_DIR)/%.o)
# Gcc will create these .d files containing dependencies.
DEP = $(OBJS:%.o=%.d)

# List of *.c source of all test program files.
C_TEST_PROGS = $(wildcard tests/*-test.c)
TEST_PROGS = $(C_TEST_PROGS:%-test.c=$(BUILD_DIR)/%-test)

# Default target
all: $(TEST_PROGS)
.PHONY: all

# Test targets - depends on all .o files.
$(BUILD_DIR)/tests/%-test: $(BUILD_DIR)/tests/%-test.o $(OBJS)
	# Create build directories - same structure as sources.
	mkdir -p $(@D)
	# Just link all the object files.
	$(CC) $(C_FLAGS) $^ -o $@

# Include all .d files
-include $(DEP)

# Build target for every single object file.
# The potential dependency on header files is covered
# by calling `-include $(DEP)`.
$(BUILD_DIR)/%.o: %.c
	mkdir -p $(@D)
	# The -MMD flags additionaly creates a .d file with
	# the same name as the .o file.
	$(CC) $(C_FLAGS) -MMD -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
