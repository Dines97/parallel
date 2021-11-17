#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <time.h>

#include <cstdlib>
#include <iomanip>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
  double static t1, t2, a1[8000000][8], a2[8000][8000], a3[8][8000000],
      b1[8000000], b2[8000], b3[8], c[8000000];
  int n1, n2, n3, k, i, j, list_length;
  int tmp, phase;
  int thread_count;
  thread_count = atoi(argv[1]);
  n1 = 8000000;
  n2 = 8000;
  n3 = 8;
  for (i = 0; i < n1; i++) {
    for (j = 0; j < n3; j++) {
      a1[i][j] = (double)(rand() % 90) + 10;
    }
    b1[i] = (double)(rand() % 90) + 10;
  }

  for (i = 0; i < n2; i++) {
    for (j = 0; j < n2; j++) {
      a2[i][j] = (double)(rand() % 90) + 10;
    }
    b2[i] = (double)(rand() % 90) + 10;
  }
  for (i = 0; i < n3; i++) {
    for (j = 0; j < n1; j++) {
      a3[i][j] = (double)(rand() % 90) + 10;
    }
    b3[i] = (double)(rand() % 90) + 10;
  }

  t1 = omp_get_wtime();

#pragma omp parallel for num_threads(thread_count) default(none) private( \
    i, j, k) shared(a1, b1, c, n1, n3)
  for (i = 0; i < n1; i++) {
    c[i] = 0.0;
    for (j = 0; j < n3; j++) c[i] += a1[i][j] * b1[j];
  }

  t2 = omp_get_wtime() - t1;
  cout << "Time elapsed a1 =" << t2 << endl;

  t1 = omp_get_wtime();

#pragma omp parallel for num_threads(thread_count) default(none) private( \
    i, j, k) shared(a2, b2, c, n2)
  for (i = 0; i < n2; i++) {
    c[i] = 0.0;
    for (j = 0; j < n2; j++) c[i] += a2[i][j] * b2[j];
  }

  t2 = omp_get_wtime() - t1;
  cout << "Time elapsed a2 =" << t2 << endl;

  t1 = omp_get_wtime();

#pragma omp parallel for num_threads(thread_count) default(none) private( \
    i, j, k) shared(a3, b3, c, n1, n3)
  for (i = 0; i < n3; i++) {
    c[i] = 0.0;
    for (j = 0; j < n1; j++) c[i] += a3[i][j] * b3[j];
  }

  t2 = omp_get_wtime() - t1;
  cout << "Time elapsed a3 =" << t2 << endl;

  t1 = omp_get_wtime();

  /*
  for (i=0;i<n;i++) {
  for (j=0;j<n;j++) {

      cout<<c[i][j]<<" ";
  }
  cout<<endl;
  }
   */

  return 0;
}
