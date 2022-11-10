#include <omp.h>

#include <iostream>

int main(int argc, char *argv[]) {
  int a[300];

#pragma omp parallel for num_threads(3) schedule(static, 1)
  for (int i = 0; i < 3; ++i) {
    for (int j = i * 99 + 1; j < i * 100 + 100; ++j) {
      a[j] = a[j - 1] + j;
    }
  }
}
