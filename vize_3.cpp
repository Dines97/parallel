#include <omp.h>

#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
  int n = 120;
  int a[n];

  a[0] = 0;
  a[40] = 54;
  a[80] = 97;

#pragma parallel for num_threads(3) schedule(static, 1)
  for (int t = 0; t < 3; t++) {
    for (int i = t * 40 + 1; i < t * 40 + 40; i++) {
      a[i] = a[i - 1] + i;
    }
  }
}
