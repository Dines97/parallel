#include <omp.h>

#include <iostream>

int main(int argc, char *argv[]) {
  int n = 100;
  double a[100][100], b[100][100], c[100][100];

#pragma omp parallel for schedule(static)
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      c[i][j] = 0.0;
      for (int k = i; k < n; k++) c[i][j] += a[i][k] * b[k][j];
    }

#pragma omp parallel for
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      c[i][j] = 0.0;
      for (int k = i; k < n; k++) {
#pragma omp critical
        c[i][j] += a[i][k] * b[k][j];
      }
    }

  double temp;


#pragma omp parallel for reduction(+ : temp) default(none) shared(a, b, n, c)
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      c[i][j] = 0.0;
      temp = 0.0;
      for (int k = i; k < n; k++) {
        temp += a[i][k] * b[k][j];
      }
      c[i][j] = temp;
    }
}
