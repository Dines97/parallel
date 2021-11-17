#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <time.h>

#include <cstdlib>
#include <iomanip>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
  double t1, t2;
  int n, k, i, j, list_length;
  int tmp, phase;
  int thread_count;
  thread_count = atoi(argv[1]);
  n = 160;
  int a[n];

  for (i = 0; i < n; i++) a[i] = (rand() % 90) + 10;

  j = 0;
  i = 0;
  while (i < n) {
    j++;
    cout << a[i] << " ";
    if (j == 20) {
      cout << endl;
      j = 0;
    }
    i++;
  }

  cout << endl;

  t1 = omp_get_wtime();

  for (phase = 0; phase < n; phase++) {
    if (phase % 2 == 0) {
      for (i = 1; i < n; i += 2) {
        if (a[i - 1] > a[i]) {
          tmp = a[i - 1];
          a[i - 1] = a[i];
          a[i] = tmp;
        }
      }
    } else {
      for (i = 1; i < n - 1; i += 2) {
        if (a[i] > a[i + 1]) {
          tmp = a[i];
          a[i] = a[i + 1];
          a[i + 1] = tmp;
        }
      }
    }
  }

  t2 = omp_get_wtime() - t1;
  cout << "Time elapsed=" << t2 << endl;

  j = 0;
  i = 0;
  while (i < n) {
    j++;
    cout << a[i] << " ";
    if (j == 20) {
      cout << endl;
      j = 0;
    }
    i++;
  }

  cout << endl;

  return 0;
}
