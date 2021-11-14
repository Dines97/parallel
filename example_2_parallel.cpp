#include <iostream>
#include <math.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

void Trap(double a, double b, int n, double &global_result_p);

int main(int argc, char *argv[]) {
  double t1, t2;
  int n;
  double global_result = 0;
  double a, b;
  int thread_count;

  if (argc != 5) {
    cout << "example_2_parallel_for takes four arguments" << endl;
    cout << "usage: example_2_parallel_for a b  num_threads #_of_trapezoid"
         << endl;
    exit(0);
  }

  a = atof(argv[1]);
  b = atof(argv[2]);
  thread_count = atoi(argv[3]);
  n = atoi(argv[4]);
  t1 = omp_get_wtime();
#pragma omp parallel num_threads(thread_count)
  Trap(a, b, n, global_result);

  t2 = omp_get_wtime() - t1;
  cout << "Area=" << global_result << endl;

  cout << "Elapsed time=" << t2 << endl;

  return 0;
}

void Trap(double a, double b, int n, double &global_result_p) {
  double h, x, my_result;
  double local_a, local_b;
  int i, local_n;
  int my_rank = omp_get_thread_num();
  int thread_count = omp_get_num_threads();
  h = (b - a) / n;
  local_n = n / thread_count;
  local_a = a + my_rank * local_n * h;
  local_b = local_a + local_n * h;
  my_result = (local_a * local_a + local_b * local_b) / 2;
  for (i = 1; i < local_n; i++) {
    x = local_a + i * h;
    my_result += x * x;
  }
  my_result = my_result * h;

#pragma omp critical
  global_result_p += my_result;
}
