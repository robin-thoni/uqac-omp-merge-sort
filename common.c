#include "common.h"
#include <stdio.h>

struct timespec get_time()
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
