#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
  double t1, t2, fib[2000];
  int n, k, i;

  int thread_count;

  if (argc != 3) {
    cout << "example_2_parallel_fibonnacci takes two arguments" << endl;
    cout << "usage: example_2_parallel_fibonacci  num_threads N" << endl;
    exit(0);
  }

  thread_count = atoi(argv[1]);
  n = atoi(argv[2]);

  fib[0] = 1;
  fib[1] = 1;

  fib[49] = 1320;
  fib[50] = 14174;

  t1 = omp_get_wtime();
#pragma omp parallel num_threads(2)
  {
#pragma omp section
    for (i = 2; i < 49; i++) {
      // SADECE TEK BIR AKIM BUNU CALISTIRIYOR
      fib[i] = fib[i - 1] + fib[i - 2];
    }
#pragma omp section
    for (i = 51; i < 100; i++){
      // SADECE TEK BIR AKIM BUNU CALISTIRIYOR
      fib[i] = fib[i - 1] + fib[i - 2];
    }
  }
  t2 = omp_get_wtime() - t1;

  cout << "Time elapsed=" << t2 << endl;

  for (i = 0; i < n; i++) cout << fib[i] << " ";
  cout << endl;
  return 0;
}
