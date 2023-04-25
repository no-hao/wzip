CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
TARGET = wzip
SRCDIR = src
INCLUDE_DIRS = -I include
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/wzip_helper.c $(SRCDIR)/file_io.c $(SRCDIR)/multi_threading.c $(SRCDIR)/output_buffer.c $(SRCDIR)/rle.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

