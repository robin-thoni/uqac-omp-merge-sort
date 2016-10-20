#include "common.h"
#include <stdio.h>
#include <stdlib.h>

struct timespec get_time(void)
{
    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    return start_time;
}

struct timespec time_diff(struct timespec* ts1, struct timespec* ts2)
{
  static struct timespec ts;
  ts.tv_sec = ts1->tv_sec - ts2->tv_sec;
  ts.tv_nsec = ts1->tv_nsec - ts2->tv_nsec;
  if (ts.tv_nsec < 0) {
    ts.tv_sec--;
    ts.tv_nsec += 1000000000;
  }
  return ts;
}

struct timespec get_duration(struct timespec* ts)
{
  struct timespec time = get_time();
  return time_diff(&time, ts);
}

void print_time(struct timespec* ts)
{
  long ns = ts->tv_nsec % 1000;
  long us = (ts->tv_nsec / 1000) % 1000;
  long ms = (ts->tv_nsec / 1000000) % 1000;
  long s =  (ts->tv_nsec / 1000000000) % 1000 + ts->tv_sec;
  long t = (s * 1000000000) + (ms * 1000000) + (us * 1000) + ns;
  printf("%3lds %3ldms %3ldus %3ldns %12ld", s, ms, us, ns, t);
}

int* read_int_array(unsigned n)
{
  int* array = (int*)malloc(n * sizeof(unsigned));
  for (unsigned i = 0; i < n; ++i) {
    scanf("%i", &array[i]);
  }
  return array;
}

void read_input(int** array, unsigned* n)
{
  printf("Enter n: ");
  scanf("%u", n);
  printf("Enter %u integers: ", 2 * *n);
  *array = read_int_array(2 * *n);
}

void print_array(int* array, unsigned n)
{
  for (unsigned i = 0; i < n; ++i) {
    printf("%i ", array[i]);
  }
  printf("\n");
}

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
