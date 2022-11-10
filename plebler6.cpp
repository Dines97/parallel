#include <omp.h>

#include <iostream>

int main(int argc, char *argv[]) {
#pragma omp parallel for num_threads(3) reduction(+ : sum) schedule(static, 3)
  for (int i = 0; i < 15; ++i) {
    sum += func1(i);
  }

  thread 0: 0,1,2, 9,10,11
  thread 1: 3,4,5, 12,13,14
  thread 2: 6,7,8


}
