# Project Name
TARGET = conch

# compiler / flags
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS =

# Source and object files
SRCDIR = src
OBJDIR = obj
INCDIR = include

SOURCES := $(wildcard $(SRCDIR)/*c)
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

# Default target
all: $(TARGET)

# Link object files into the final binary
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

# Compile each source file into an object file
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# clean up build files
clean:
	rm -rf $(OBJDIR) $(TARGET)

# rebuild everything from scratch
rebuild: clean all

.PHONY: all clean rebuild
