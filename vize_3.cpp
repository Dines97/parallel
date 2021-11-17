#include <omp.h>

#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
  int n = 120;
  int a[n];

  a[0] = 0;
  a[39] = 54;
  a[79] = 97;

#pragma parallel for num_threads(3)
  for (int t = 0; t < 3; t++) {
    for (int i = t * 40 + 1; i < t * 40 + 39; i++) {
      a[i] = a[i - 1] + i;
    }
  }
}
