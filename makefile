CC := gcc
CFLAGS := -g -Wall -Iinclude
LDFLAGS :=

SRCDIR := src
OBJDIR := src
BUILDDIR := build
BINDIR := bin

FILES := main parser trim start_services check_service
OBJFILES := $(addprefix $(BUILDDIR)/, $(FILES:=.o))

TARGET := $(BINDIR)/main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJFILES) $(TARGET) *~