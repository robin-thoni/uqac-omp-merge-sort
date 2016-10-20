#ifndef COMMON_H
#define COMMON_H

#define _POSIX_C_SOURCE 199309L
#include <time.h>

struct timespec get_time();
struct timespec time_diff(struct timespec* ts1, struct timespec* ts2);
struct timespec get_duration(struct timespec* ts);
void print_time(struct timespec* ts);

#endif
