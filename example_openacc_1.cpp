#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <omp.h>
#include <openacc.h>
#include <stdio.h>
#include <time.h>
using namespace std;

int main(int argc, char *argv[]) {
  int n, k, i, j, list_length;
  n = 10000000;
  double tmp1, y, x;
  int thread_count;
  clock_t t1, t2;
  // double  t1,t2,x,n_x;
  thread_count = atoi(argv[1]);
  tmp1 = 0;
  // t1 = omp_get_wtime();
  t1 = clock();
  y = 1.0 / ((double)n);

#pragma acc parallel loop reduction(+ : tmp1)
  for (i = 0; i < n; i++) {
    double x = (((double)i + 0.5) / n);
    tmp1 += (4.0 / (1.0 + x * x));
  }
  t2 = clock() - t1;
  // t2=omp_get_wtime()-t1;
  cout << "Time elapsed=" << t2 << endl;
  cout << tmp1 * y << " thread count=" << thread_count << endl;

  return 0;
}
