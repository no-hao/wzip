CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = wzip
SRCDIR = src
BINDIR = .

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRCDIR)/$(TARGET).c -o $(BINDIR)/$(TARGET)

clean:
	rm -f $(BINDIR)/$(TARGET)

.PHONY: all clean
