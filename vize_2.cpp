#include <omp.h>

#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
  int n = 120;
  int a[n];

  a[0] = 0;
  a[39] = 74;
  a[79] = 98;
#pragma omp parallel for num_threads(3) schedule(static, 1)
  for (int t = 0; t < 3; t++) {
    for (int i = t * 40; i < t * 40 + 39; i++) {
      a[i] = a[i - 1] + i;
    }
  }
}
