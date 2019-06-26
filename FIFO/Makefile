# Toolchain path
#TCPATH = aarch64-linux-gnu-
TCPATH ?=

# Kernel Headers path
KERNELHEADERS = /usr/include/
INCLUDES = -I$(KERNELHEADERS) -I/usr/local/include/

CC := ${TCPATH}gcc
CFLAGS = -Wall -g
LDFLAGS = -lm

#SRCDIR = src
SOURCES1 = src/write.c
OBJECTS1 := $(SOURCES1:.c=.o)
EXEC1 = writefifo

SOURCES2 = src/read.c
OBJECTS2 := $(SOURCES2:.c=.o)
EXEC2 = readfifo

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJECTS1)
	$(CC) $(CFLAGS) -static -o $(EXEC1) $(OBJECTS1) $(LDFLAGS)

$(EXEC2): $(OBJECTS2)
	$(CC) $(CFLAGS) -static -o $(EXEC2) $(OBJECTS2) $(LDFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $<

clean:
	rm -rf $(OBJECTS1) $(EXEC1) $(OBJECTS2) $(EXEC2)

install:

.PHONY: clean all
