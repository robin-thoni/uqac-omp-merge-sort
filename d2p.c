#include "d2p.h"
#include "common.h"
#include "d2s.h"

void merge_sort_sub_par(int* array, unsigned l, unsigned h, unsigned threads)
{
  if (l < h) {
    unsigned m = (l + h) / 2;
    if (threads > 1) {
      unsigned n = threads / 2;
      #pragma omp parallel sections
      {
        #pragma omp section
        merge_sort_sub_par(array, l, m, threads);
        #pragma omp section
        merge_sort_sub_par(array, m + 1, h, threads - n);
      }
    }
    else {
      merge_sort_sub_seq(array, l, m);
      merge_sort_sub_seq(array, m + 1, h);
    }
    merge_sort_merge_seq(array, l, m, h);
  }
}

void merge_sort_par(int* array, unsigned s, unsigned threads)
{
  merge_sort_sub_par(array, 0, s - 1, threads);
}
