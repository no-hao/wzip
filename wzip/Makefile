CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = wzip
SRCDIR = src
INCLUDE_DIRS = -I include
SOURCES = $(SRCDIR)/$(TARGET).c $(SRCDIR)/wzip_helper.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -o $@ $^ -pthread

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
