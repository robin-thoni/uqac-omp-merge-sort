#include <stdio.h>
#include <omp.h>
#include "d2p.h"
#include "common.h"
#include "d2s.h"

void merge_sort_sub_par(int* array, unsigned l, unsigned h)
{
  if (l < h) {
    unsigned m = (l + h) / 2;
    #pragma omp task
      merge_sort_sub_par(array, l, m);
    #pragma omp task
      merge_sort_sub_par(array, m + 1, h);
    #pragma omp taskwait
    merge_sort_merge_seq(array, l, m, h);
  }
}

void merge_sort_par(int* array, unsigned s, unsigned threads)
{
  omp_set_num_threads(threads);
#pragma omp parallel
  {
#pragma omp single
    {
      merge_sort_sub_par(array, 0, s - 1);
    }
  }
}
