#include "common.h"

void merge_sort_merge_seq(int* array, unsigned l, unsigned m, unsigned h)
{
  unsigned i = l, j = m + 1, k = 0;
  int tmp[h - l + 1];
  while (i <= m && j <= h) {
    if (array[i] <= array[j]) {
      tmp[k++] = array[i++];
    }
    else {
      tmp[k++] = array[j++];
    }
  }

  while (i <= m) {
    tmp[k++] = array[i++];
  }
  while (j <= h) {
    tmp[k++] = array[j++];
  }

  for (--k; k != (unsigned)-1; --k) {
    array[l + k] = tmp[k];
  }
}

void merge_sort_sub_seq(int* array, unsigned l, unsigned h)
{
  if (l < h) {
    unsigned m = (l + h) / 2;
    merge_sort_sub_seq(array, l, m);
    merge_sort_sub_seq(array, m + 1, h);
    merge_sort_merge_seq(array, l, m, h);
  }
}

void merge_sort_seq(int* array, unsigned s)
{
  merge_sort_sub_seq(array, 0, s - 1);
}
