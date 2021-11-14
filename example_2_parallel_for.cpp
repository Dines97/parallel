#include <iomanip>
#include <iostream>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main(int argc, char *argv[]) {
  double t1, t2;
  int n, i;
  double global_result = 0;
  double a, b, h, approx, x, sum1, a1, temp, y;
  int thread_count;

  if (argc != 5) {
    cout << "example_2_parallel_fot_for takes four arguments" << endl;
    cout << "usage: example_2_parallel_for a b  num_threads N" << endl;
    exit(0);
  }

  a = atof(argv[1]);
  b = atof(argv[2]);
  thread_count = atoi(argv[3]);
  n = atoi(argv[4]);
  t1 = omp_get_wtime();
  h = (b - a) / n;
  approx = (a * a + b * b) / 2;

  /*
#pragma omp parallel for num_threads(thread_count)  reduction(+:approx)
private(x) firstprivate(h) firstprivate(a) for ( i=1;i<=n;i++) //
(a+i*h)*(a+i*h);
{
    x=a+i*h;
    approx+=(x*x);//(a+i*h)*(a+i*h);

}
*/

#pragma omp parallel num_threads(thread_count) private(x) firstprivate(h)      \
    firstprivate(a) // reduction(+:approx)
  {
    double temp;
    temp = 0;
    // #pragma omp  for
    for (i = 1; i <= n; i++) // (a+i*h)*(a+i*h);
    {
      x = a + i * h;
      temp += (x * x); //(a+i*h)*(a+i*h);
    }
#pragma omp critical
    approx += temp;
  }

  cout << "Area=" << h * approx << endl;

  t2 = omp_get_wtime() - t1;
  cout << "Time elapsed=" << t2 << endl;
  cout << setprecision(15) << "x=" << x << "y=" << y << endl;

  return 0;
}
