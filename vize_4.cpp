#include <omp.h>

#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
  int n = 100;
  double a[n][n];
  double b[n][n];
  double c[n][n];

  int i, j, k, tmp = 0;

  await load_images()
  await load_textures()

#pragma omp parallel for num_threads(5) default(none) private(i, j, k) \
    shared(n, a, b, c) reduction(+ : tmp) collapse(2)
  for (i = 0; i < n; i++) {

    for (j = 0; j < n; j++) {
      c[i][j] = 0.0;
#pragma omp parallel for
      for (k = 0; k < n; k++) {
        tmp += a[i][k] * b[k][j];
      }
      c[i][j] = tmp;
    }
  }
}