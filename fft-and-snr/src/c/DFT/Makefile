# Toolchain path
#TCPATH = aarch64-linux-gnu-
TCPATH ?=

# Kernel Headers path
KERNELHEADERS = /usr/include/

CC := ${TCPATH}gcc
CFLAGS = -Wall -g
LDFLAGS = -lm -lpthread

INCLUDES = -I$(KERNELHEADERS) -I/usr/local/include/

SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(SOURCES:.c=.o)
EXEC = dft

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJECTS) $(LDFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $<

clean:
	rm -f $(OBJECTS) $(EXEC)

install:

.PHONY: clean alls
