#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <omp.h>
using namespace std;

double Trap(double a, double b, int n);
int main(int argc, char *argv[]) {
  double t1, t2;
  int n, thread_count;
  double global_result;
  double a, b;

  if (argc != 5) {
    cout << "example_2_parallel_for takes four arguments" << endl;
    cout << "usage: example_2_parallel_for a b  num_threads N" << endl;
    exit(0);
  }

  a = atof(argv[1]);
  b = atof(argv[2]);
  thread_count = atoi(argv[3]);
  n = atoi(argv[4]);

  t1 = omp_get_wtime();

  global_result = 0;

#pragma omp parallel num_threads(thread_count) reduction(+ : global_result)
  global_result += Trap(a, b, n);

  /*
      #pragma omp parallel num_threads(thread_count)
      {double my_result;
          my_result=Trap(a,b,n);
      # pragma omp critical
      global_result+=my_result;  //my_result;
      }



      #pragma omp parallel num_threads(thread_count)
      {
          #pragma  omp critical
          global_result+=Trap(a,b,n);
      }
    */

  t2 = omp_get_wtime() - t1;

  cout << "Area=" << global_result << endl;

  cout << "Time elapsed =" << t2 << endl;
  return 0;
}

double Trap(double a, double b, int n)

{
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
  // cout<<my_result<<endl;
  return my_result;
}
