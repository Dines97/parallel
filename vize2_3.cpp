#include <omp.h>

#include <iostream>

int main(int argc, char *argv[]) {
#pragma omp parallel for num_threads(4) schedule(dynamic, 4)
  for (int i = 0; i < 20; ++i) {
#pragma omp critical
    std::cout << omp_get_thread_num() << ": " << i << std::endl;
  }
}
