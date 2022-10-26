//------------------------------------------------------------------------------
//
// Mixed mode tuple generation app and tests
//
//------------------------------------------------------------------------------
//
// This file is licensed after LGPL v3
// Look at: https://www.gnu.org/licenses/lgpl-3.0.en.html for details
//
//------------------------------------------------------------------------------

#include <stdio.h>

#include "comb.h"

static void print_arr(int *first, int *last) {
  for (int *p = first; p != last; ++p)
    printf("%d ", *p);
  printf("\n");
}

static void test2134() {
  int borders[] = {2, 1, 3, 4};
  int arr[] = {0, 0, 0, 0};
  int k = 1;

  while (k == 1) {
    print_arr(arr, arr + 4);
    k = next_mm_tuple_of(arr, arr + 4, borders);
  }

  printf("Restored array:\n");
  print_arr(arr, arr + 4);
}

static void test2134_loopless() {
  int m[] = {2, 2, 3, 4};
  int a[] = {0, 0, 0, 0}; // a(n-1) .. a(0)

  struct loopless_state *st = create_loopless_state(4);
  int k = 1;

  printf("Loopless:\n");
  while (k != 0) {
    if (k != -1)
      print_arr(a, a + 4);
    k = loopless_next_mm_tuple_of(a, a + 4, m, st);
  }
  printf("Restored array:\n");
  print_arr(a, a + 4);

  free_loopless_state(st);
}

int main() {
  test2134();
  test2134_loopless();
}