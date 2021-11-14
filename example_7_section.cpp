#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <time.h>
using namespace std;

double f1(double a2[16000][16000], double b2[16000], double c2[16000], int n) {
  double temp = 0;
  int i, j, n2;
  n2 = n;
  {
    for (i = 0; i < n2; i++) {
      c2[i] = 0.0;
      for (j = 0; j < n2; j++)
        c2[i] += a2[i][j] * b2[j];
      temp = temp + c2[i];
    }
  }
  return temp;
}

double f2(double a[1024][1024], double b[1024][1024], double c[1024][1024],
          int nn) {
  double temp = 0;
  int i, j, n, k;
  n = nn;
  {
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
        c[i][j] = 0.0;
        for (k = 0; k < n; k++)
          c[i][j] += a[i][k] * b[k][j];
        temp = temp + c[i][j];
      }
    }
  }

  return temp;
}

int main(int argc, char *argv[]) {
  double static t1, t2, a[1024][1024], b[1024][1024], c[1024][1024],
      d[1024][1024], a2[16000][16000], b2[16000], c2[16000], temp1, temp2;
  int n, n2, k, i, j, list_length;
  int tmp, phase;
  int thread_count;
  thread_count = atoi(argv[1]);
  int my_rank = omp_get_thread_num();
  n = 400;    // n=400;
  n2 = 15000; // n2=15000;

  for (j = 0; j < n; j++) {
    for (i = 0; i < n; i++) {
      a[i][j] = (double)(rand() % 90) + 10;
      b[i][j] = (double)(rand() % 90) + 10;
      d[j][i] = b[i][j];
    }
  }

  for (i = 0; i < n2; i++) {
    for (j = 0; j < n2; j++) {
      a2[i][j] = (double)(rand() % 90) + 10;
    }
    b2[i] = (double)(rand() % 90) + 10;
  }

  t1 = omp_get_wtime();

  //#pragma omp parallel
  //#pragma omp  sections

  /*
  #pragma omp parallel sections num_threads(thread_count)
  {
  #pragma omp section
  temp1=f1(a2, b2, c2,n2);
  #pragma omp section
  {//temp2=f2(a, b, c,n);


     temp2=0; int i,j,k;

     {
      for( i=0; i<n; i++ ) {
  for( j=0; j<n; j++ ) {
  c[i][j] = 0.0;
  for( k=0; k<n; k++ ) c[i][j] += a[i][k]*b[k][j];
      temp2=temp2+c[i][j];
  }
  }
       }

  }
  }
  */

#pragma omp parallel num_threads(thread_count)
  for (j = 0; j < thread_count; j++) {
    my_rank = omp_get_thread_num();
    if (my_rank == 0) {
      temp1 = f1(a2, b2, c2, n2);
    } else if (my_rank == 1)
      temp2 = f2(a, b, c, n);
  }

  t2 = omp_get_wtime() - t1;
  cout << "elapsed time=" << t2 << endl;
  cout << setprecision(15) << temp1 << "   " << temp2 << endl;
  return 0;
}
