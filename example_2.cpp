#include <math.h>
#include <omp.h>
#include <time.h>

#include <iostream>
// PS1='Z:\W\$ '

using namespace std;
class area {
 public:
  double a, b;
  double compute_area(int);
  area(double x, double y) {
    a = x;
    b = y;
  }
};

double area::compute_area(int num_step) {
  int i;
  double h, approx, x;
  h = (b - a) / num_step;
  approx = (a * a + b * b) / 2;
  x = a;
  for (i = 1; i < num_step; i++) {
    x += h;
    approx += x * x;
  }
  approx = h * approx;

  return approx;
}

int main(int argc, char* argv[]) {
  double t1, t2, a, b;
  int n, j;
  if (argc != 4) {
    cout << "example_3 takes three arguments" << endl;
    cout << "usage: example_2 no_of_steps a b " << endl;
    exit(0);
  }
  n = atoi(argv[1]);
  a = atof(argv[2]);
  b = atof(argv[3]);
  area z_area(a, b);
  t1 = omp_get_wtime();
  // for (j=1;j<5;j++) {z_area.compute_area(n);}
  cout << "Area of the function x^2 from " << a << " to " << b << " ="
       << z_area.compute_area(n) << endl;

  t2 = omp_get_wtime() - t1;
  cout << "Elapsed time =" << t2 << endl;

  return 0;
}
