#
# Makefile
#

CC ?= gcc
LD ?= $(CC)
CFLAGS = 

all: cat.386BSD-Release cat.Bell-Release

cat.386BSD-Release: cat.386BSD-Release.now.c
	$(CC) $(CFLAGS) $< -o $@

cat.Bell-Release: cat.Bell-Release.now.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -fv cat.386BSD-Release cat.Bell-Release 
	rm -fv test*

test: test-386 test-Bell

test-386: cat.386BSD-Release 
	./cat.386BSD-Release README.md > test.386
	diff README.md test.386 

test-Bell: cat.Bell-Release 
	./cat.Bell-Release README.md > test.Bell
	diff README.md test.Bell 

.PHONY: all clean test test-386 test-Bell 
