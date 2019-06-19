# Toolchain path
#TCPATH = aarch64-linux-gnu-
TCPATH ?=

# Kernel Headers path
KERNELHEADERS = /usr/include/
INCLUDES = -I$(KERNELHEADERS) -I/usr/local/include/

CC := ${TCPATH}gcc
CFLAGS = -Wall -g
LDFLAGS = -lm

SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(SOURCES:.c=.o)
EXEC = float2byte

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -static -o $(EXEC) $(OBJECTS) $(LDFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $<

clean:
	rm -rf $(OBJECTS) $(EXEC)

install:

.PHONY: clean all
