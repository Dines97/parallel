#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <time.h>
using namespace std;

int main(int argc, char *argv[]) {
  double static a[4096], tmp, tmp1;
  int n, n2, k, i, j, list_length, n1;

  int thread_count;
  thread_count = atoi(argv[1]);
  n = 200;
  n1 = 1024 * 1024;
  double t1, t2;

  for (i = 0; i < n; i++)
    a[i] = (double)i;

//#pragma omp simd aligned(a)
#pragma omp parallel for num_threads(thread_count) shared(a, n)                \
    schedule(dynamic, 3)
  for (i = 0; i < n; i++)
    a[i] += a[i + 9];

  //#pragma omp parallel for   num_threads(thread_count) shared(x,y,z,n1,n)
  //private(j,i) ////reduction(+:tmp,tmp1)

  cout << a[0] << " ";
  for (i = 1; i < n; i++) {
    cout << a[i] << " ";
    if ((i % 20) == 0)
      cout << endl;
  }

  return 0;
}
