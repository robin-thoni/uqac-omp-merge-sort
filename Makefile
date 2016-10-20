CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -fopenmp
LDLIBS = -lrt
CC = gcc
SOURCES_COMMON = common.c
SOURCES_SEQ = $(SOURCES_COMMON) d2s.c
OUT_SEQ = omp-merge-sort-seq
OBJS_SEQ = $(SOURCES_SEQ:.c=.o)
SOURCES_PAR = $(SOURCES_COMMON) d2p.c
OUT_PAR = omp-merge-sort-par
OBJS_PAR = $(SOURCES_PAR:.c=.o)

all: release

debug: CFLAGS += -g3 -ggdb3
debug: $(OUT_SEQ) $(OUT_PAR)

release: CFLAGS += -o3
release: $(OUT_SEQ) $(OUT_PAR)

$(OUT_SEQ): $(OBJS_SEQ)
	  $(LINK.c) $(OUTPUT_OPTION) $(OBJS_SEQ) $(LDLIBS)

$(OUT_PAR): $(OBJS_PAR)
	  $(LINK.c) $(OUTPUT_OPTION) $(OBJS_PAR) $(LDLIBS)

clean:
	  rm -f *.o

distclean: clean
	  rm -f *.a $(OUT_SEQ) $(OUT_PAR)
