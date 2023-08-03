# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Source files and executable name
SOURCE_FILES = pe.c
EXECUTABLE = pe

# Targets and dependencies
all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE_FILES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCE_FILES) -lm

clean:
	rm -f $(EXECUTABLE)
