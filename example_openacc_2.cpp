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
  n = 1000;
  double tmp1, y, x, error;
  int thread_count, iter, iter_max;
  clock_t t1, t2;
  double static A[1024][1024], Anew[1024][1024];
  // double  t1,t2,x,n_x;
  thread_count = atoi(argv[1]);
  tmp1 = 0;
  // t1 = omp_get_wtime();
  t1 = clock();

  for (j = 0; j < n; j++) {
    for (i = 0; i < n; i++) {
      A[i][j] = (double)(rand() % 90) + 10;
    }
  }
  iter = 0;
  iter_max = 1000;
#pragma acc data copy(A) create(Anew)
  {
    while (iter < iter_max) {
      error = 0.0;
#pragma acc parallel loop
      for (int j = 1; j < 999; j++) {
        for (int i = 1; i < 999; i++) {
          Anew[j][i] =
              0.25 * (A[j][i + 1] + A[j][i - 1] + A[j - 1][i] + A[j + 1][i]);
          error = max(error, abs(Anew[j][i] - A[j][i]));
        }
      }
#pragma acc parallel loop
      for (int j = 1; j < 999; j++) {
        for (int i = 1; i < 999; i++) {
          A[j][i] = Anew[j][i];
        }
      }
      iter++;
    }
  }
  for (j = 0; j < n; j++) {
    for (i = 0; i < n; i++) {
      tmp1 += A[i][j];
    }
  }

  t2 = clock() - t1;
  cout << "Time elapsed=" << t2 << endl;
  cout << tmp1 << " thread count=" << thread_count << endl;

  return 0;
}
