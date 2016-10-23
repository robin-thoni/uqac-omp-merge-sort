#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "common.h"
#include "d2s.h"
#include "d2p.h"

int main(int argc, char** argv)
{
  int oprint_stats = 1;
  int oprint_array = 1;
  int otest = 0;

  for (int i = 1; i < argc; ++i) {
    if (!strcmp("--no-stats", argv[i])) {
      oprint_stats = 0;
    }
    else if (!strcmp("--no-array", argv[i])) {
      oprint_array = 0;
    }
    else if (!strcmp("--test", argv[i])) {
      otest = 1;
    }
  }
  if (otest) {
    oprint_stats = 0;
    oprint_array = 1;
  }

  int* array;
  unsigned n;
  unsigned threads[3] = {0, 12, 24};
  unsigned threads_count = (otest ? 1 : sizeof(threads) / sizeof(*threads));

  do {
    read_input(&array, &n);
    if (array && n) {
      for (unsigned t = 0; t < threads_count; ++t) {
        unsigned thread_count = threads[t];
        struct timespec start = get_time();
        if (thread_count == 0) {
          merge_sort_seq(array, 2 * n);
        }
        else {
          merge_sort_par(array, 2 * n, thread_count);
        }
        struct timespec ts = get_duration(&start);
        if (oprint_array) {
          print_array(array, 2 * n);
        }
        if (oprint_stats) {
          printf("%3dcpu %3dthreads %6d ", get_cpu_count(), thread_count, n);
          print_time(&ts);
          printf("\n");
        }
      }
    }
  } while (array && n);

  return 0;
}
