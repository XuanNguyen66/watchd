CC := gcc
CFLAGS := -g -Wall -Iinclude
LDFLAGS := -L/usr/local/lib -lcunit

SRCDIR := src
OBJDIR := src
BUILDDIR := build
BINDIR := bin
TESTDIR := tests/unit

FILES := main parser trim start_services check_service become_daemon write_log
OBJFILES := $(addprefix $(BUILDDIR)/, $(FILES:=.o))

TARGET := $(BINDIR)/main
TEST_SRCS := $(wildcard $(TESTDIR)/test_*.c)
TEST_BINS := $(patsubst $(TESTDIR)/%.c, $(BINDIR)/%, $(TEST_SRCS))
TEST_OBJS := $(filter-out $(BUILDDIR)/main.o, $(OBJFILES))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# $(BINDIR)/test_%: $(TESTDIR)/test_%.c  $(BINDIR)
# 	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
$(BINDIR)/test_%: $(TESTDIR)/test_%.c $(TEST_OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $< $(TEST_OBJS) $(LDFLAGS)

test: $(TEST_BINS)
	@for t in $(TEST_BINS); do \
		echo "=== Running $$t ==="; \
		./$$t || exit 1; \
	done

clean:
	rm -f $(OBJFILES) $(TARGET) *~