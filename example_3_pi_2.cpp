#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iomanip>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
  double t1, t2;
  int n, k, i;
  double global_result = 0;
  double pi_approx, sum;
  int thread_count;
  thread_count = atoi(argv[1]);

  double factor = 1.0;
  sum = 0.0;
  n = 300000000;
  t1 = omp_get_wtime();
  // #pragma omp parallel for num_threads(thread_count)  reduction(+:sum)
  //{
  // double factor=1.0;
#pragma omp parallel for num_threads(thread_count)  private(k) reduction(+:sum) firstprivate(factor) schedule(static,1)
  for (k = 0; k < n; k += 2) {
    sum += factor / (2 * k + 1) - (factor / (2 * (k + 1) + 1));

  }  //}
  pi_approx = 4.0 * sum;

  t2 = omp_get_wtime() - t1;

  cout << "The value of pi=" << setprecision(20) << pi_approx << endl;
  cout << "Time elapsed=" << t2 << endl;

  return 0;
}
