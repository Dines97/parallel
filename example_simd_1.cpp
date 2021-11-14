#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <time.h>
using namespace std;

int main(int argc, char *argv[]) {
  double static a[4096][4096], b[4096][4096], c[4096][4096], d[4096][4096],
      x[1024 * 1024], y[1024 * 1024], z[1024 * 1024], tmp, tmp1;
  int n, n2, k, i, j, list_length, n1;

  int thread_count;
  thread_count = atoi(argv[1]);
  n = 1024;
  n1 = 1024 * 1024;
  double t1, t2;
  for (j = 0; j < n; j++) {
    for (i = 0; i < n; i++) {
      a[i][j] = (double)(rand() % 90) + 10;
      b[i][j] = (double)(rand() % 90) + 10;
      d[j][i] = b[i][j];
      c[i][j] = 0;
    }
  }
  for (i = 0; i < n1; i++) {
    x[i] = 0.1 * ((double)(rand() % 90) + 10);
    y[i] = 0.1 * ((double)(rand() % 90) + 10);
    z[i] = 0;
  }

  t1 = omp_get_wtime();
  tmp = 0;

#pragma omp parallel for num_threads(thread_count) default(none)  private(i,j,k) shared(a,d,c,n) reduction(+:tmp)
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      tmp = 0;
#pragma omp simd aligned(a, d, c) reduction(+ : tmp)
      for (k = 0; k < n; k++)
        tmp += (a[j][k] * d[j][k]);
      c[i][j] = tmp;
    }
  }
  /*
  n2=n;
  tmp1=0;
  tmp=0;
   #pragma omp parallel for   num_threads(thread_count) shared(x,y,z,n1,n)
  private(j,i)
  ////reduction(+:tmp,tmp1)
  for (j=0;j<n;j++) {
  //#pragma omp simd  aligned(x,y,z) reduction(+:tmp1)
   for (i=0;i<n1;i++) {
       z[i]=x[i]*y[i];
       tmp1+=z[i];
   }

  }
  */
  t2 = omp_get_wtime() - t1;
  cout << "Time elapsed=" << t2 << endl;

  /*  tmp=0;

 for( i=0; i<n; i++ ) {
 for( j=0; j<n; j++ ) {
  tmp+= c[i][j];}
 }
 */

  /*
     tmp=0;
  for( i=0; i<n1; i++ ) {
   tmp+= z[i];
  }
  */

  cout << tmp << " thread count=" << thread_count << endl;
  cout << z[0] << " " << z[1] << " " << z[2] << " " << z[3] << " " << z[4]
       << " " << endl;
  cout << "tmp1=" << tmp1 << endl;
  // cout<<"tmp="<<tmp<<endl;
  return 0;
}
