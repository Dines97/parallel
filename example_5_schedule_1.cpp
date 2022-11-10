#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <time.h>

#include <cstdlib>
#include <iomanip>
#include <iostream>
using namespace std;
double func1(int i) {
  int j, start, finish;
  double return_value = 0.0;
  start = (i * (i + 1)) / 2;
  finish = start + i;  //(10010-i); //i;
  for (j = start; j <= finish; j++) {
    return_value += sin((double)j);
  }
  return return_value;
}

int main(int argc, char* argv[]) {
  double t1, t2, sum;
  int n, k, i, j;
  int thread_count;
  thread_count = atoi(argv[1]);
  n = 10000;  // 30;

  t1 = omp_get_wtime();
  sum = 0.0;
#pragma omp parallel for num_threads(thread_count) reduction(+:sum) schedule(guided, 100) //schedule(static,1) //schedule(guided,1) //schedule(static,1)
  for (i = 0; i <= n; i++) {
    thread 0: 0....100,
    thread 1: 0...50,
    thread 2: 3
    thread 3: 5

    sum += func1(i);
  }


  t2 = omp_get_wtime() - t1;
  cout << "Time elapsed=" << t2 << endl;
  cout << "SUM=" << sum << endl;

  return 0;
}
