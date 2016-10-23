CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -fopenmp
LDLIBS = -lrt
CC = gcc
SOURCES = common.c d2s.c d2p.c main.c
OUT = omp-merge-sort
OBJS = $(SOURCES:.c=.o)

all: release

debug: CFLAGS += -g3 -ggdb3
debug: $(OUT)

release: CFLAGS += -o3
release: $(OUT)

$(OUT): $(OBJS)
	  $(LINK.c) $(OUTPUT_OPTION) $(OBJS) $(LDLIBS)

clean:
	  rm -f *.o

distclean: clean
	  rm -f *.a $(OUT)
