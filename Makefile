# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror

# Executable name
TARGET = sport_db

# Source files
SRCS = sport_db.c sport_db_event.c sport_db_athlete.c

# Object files (each .c file will be compiled into a .o file)
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = sport_db.h sport_db_event.h sport_db_athlete.h

# Default target: build the executable
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile each .c file into a .o file
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -f $(TARGET) $(OBJS)

# PHONY targets to avoid conflicts with files named 'clean'
.PHONY: clean