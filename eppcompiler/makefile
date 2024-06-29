CC = g++

SRCDIR = src
INCDIR = include
TESTDIR = tests
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
TEST_SOURCE = $(TESTDIR)/main.cpp

CFLAGS = -I$(INCDIR) -Wall -O3 -w -std=c++17

TARGET = $(BINDIR)/e++

$(TARGET): $(SOURCES) $(TEST_SOURCE)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "Compiler Built Successfully !!"

clean:
	rm -f $(TARGET)

.PHONY: clean