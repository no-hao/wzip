CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = wzip
SRCDIR = src
BINDIR = .

INCLUDE_DIRS = -I../include

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(SRCDIR)/$(TARGET).c $(SRCDIR)/wzip_helper.c -o $(BINDIR)/$(TARGET)

clean:
	rm -f $(BINDIR)/$(TARGET)

.PHONY: all clean
