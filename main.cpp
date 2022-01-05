#include <omp.h>

#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
  int i;
  int n = 120;
  int a[n];

  a[0] = 0;
  for (i = 1; i < n; i++) {
    a[i] = a[i - 1] + i;
  }
}
