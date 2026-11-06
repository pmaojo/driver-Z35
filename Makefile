CC ?= cc
CFLAGS ?= -O2 -Wall -Wextra
LDLIBS = -lcups
all: build/rastertoz35
build/rastertoz35: filter/rastertoz35.c filter/z35_encode.c filter/z35_encode.h
	@mkdir -p build
	$(CC) $(CFLAGS) -o $@ filter/rastertoz35.c filter/z35_encode.c $(LDLIBS)
clean:
	rm -rf build
