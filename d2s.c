#include "common.h"

int main(void)
{
  int* array;
  unsigned n;
  read_input(&array, &n);
  merge_sort_seq(array, 2 * n);
  print_array(array, 2 * n);
  return 0;
}
