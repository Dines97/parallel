#include <omp.h>

#include <iostream>

int main(int argc, char* argv[]) {
  int n = 3;
  double a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double b[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double c[n][n];

  // a is upper triangular
  int i, j, k;
#pragma omp parallel for collapse(2) schedule(dynamic, 1) default(none) shared(n, a, b, c) private(k, i, j)
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      c[i][j] = 0.0;
      for (k = i; k < n; ++k) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }

  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      std::cout << c[i][j] << " ";
    }
    std::cout << std::endl;
  }
}
