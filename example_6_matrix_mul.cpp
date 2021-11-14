#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <time.h>
using namespace std;

int main(int argc, char *argv[]) {
  double static t1, t2, a[1024][1024], b[1024][1024], c[1024][1024],
      d[1024][1024];
  int n, k, i, j, list_length;
  int tmp, phase;
  int thread_count;
  thread_count = atoi(argv[1]);
  n = 1000;

  for (j = 0; j < n; j++) {
    for (i = 0; i < n; i++) {
      a[i][j] = (double)(rand() % 90) + 10;
      b[i][j] = (double)(rand() % 90) + 10;
      d[j][i] = b[i][j];
    }
  }
  n = 10;
  t1 = omp_get_wtime();

#pragma omp parallel for num_threads(thread_count) default(none) private(      \
    i, j, k) shared(a, b, c, d, n)
  for (i = 0; i < n; i++) {
    // #pragma omp simd aligned(a,b,c) //simdlen(32) aligned(a,b,c)
    for (j = 0; j < n; j++) {
      c[i][j] = 0.0;
      // #pragma omp simd  simdlen(32) aligned(a,b,c)
      for (k = 0; k < n; k++)
        c[i][j] += a[i][k] * b[k][j];
    } // a[i][k]*d[j][k];}  //a[i][k]*b[k][j];} // a[i][k]*d[j][k];}  //
  }

  t2 = omp_get_wtime() - t1;
  cout << "Time elapsed=" << t2 << endl;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {

      cout << c[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}
