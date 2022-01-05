#include <omp.h>

#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
  int n = 120;  // Assume n equals 120
  int a[n];

  a[0] = 0;
  a[40] = 20;
  a[80] = 60;

  int i;
  int t;

#pragma omp parallel for num_threads(3) schedule(static, 1) private(i, t) shared(a)
  for (t = 0; t < 3; t++) {
    for (i = t * 40 + 1; i < t * 40 + 40; i++) {
      a[i] = a[i - 1] + i;
    }
  }
}
