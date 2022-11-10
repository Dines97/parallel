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
  int tmp;
  int thread_count;
  thread_count = atoi(argv[1]);
  n = 160;
  n = 10;
  int a[n];
  srand(time(NULL));
  for (i = 0; i < n; i++) a[i] = (rand() % 9000) + 10;

  j = 0;
  i = 0;

  /*  while (i<n)
{j++;
    cout<<a[i]<<" ";
    if (j==20) {cout<<endl;j=0;}
    i++;
}
 cout<<endl;*/

  t1 = omp_get_wtime();
#pragma omp parallel for num_threads(2048) private(tmp)
  for (list_length = n; list_length >= 2; list_length--) {
    for (i = 0; i < list_length - 1; i++) {
      if (a[i] > a[i + 1]) {
        tmp = a[i];
        a[i] = a[i + 1];
        a[i + 1] = tmp;
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
