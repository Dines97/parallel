#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <time.h>
using namespace std;

#pragma omp declare simd
float f(float x) { return (4.0 / (1.0 + x * x)); }

int main(int argc, char *argv[]) {
  int n, k, i, j, list_length;
  n = 100000000;
  float tmp[4], y;
  int thread_count;
  float t1, t2;
  float x, tmp1, n_x;
  thread_count = atoi(argv[1]);
  tmp1 = 0;
  n_x = 1.0 / ((float(n)));
  t1 = omp_get_wtime();

  for (i = 0; i < 4; i++)
    tmp[i] = 0;
  x = 0;

#pragma omp parallel for  num_threads(thread_count) private(x) reduction(+:tmp1)
  //#pragma omp  simd  private(x) reduction(+:tmp1)
  //  #pragma acc parallel loop reduction(+:tmp1)
  for (i = 0; i < n; i++) {
    float x = (((float)i + 0.5) / n);
    tmp1 += f(x);
    // tmp1+=(4.0/(1.0+x*x));//f(x);
  }

  // for( i=0; i<4; i++ ) tmp1+=tmp[i];
  t2 = omp_get_wtime() - t1;
  cout << "Time elapsed=" << t2 << endl;
  cout << "Value=" << n_x * tmp1 << endl
       << " thread count=" << thread_count << endl;

  return 0;
}
