#include <iostream>
#include <omp.h>
/*
#ifdef _OPENMP
# include <omp.h>
#endif
*/
// PS1='Z:\W\$ '
using namespace std;
void Hello(void);
int main(int argc, char *argv[]) { /*int i;cout<<argc<<endl;
                                      for (i=0;i<argc;i++) cout<<argv[i]<<endl;
                                      cout<<endl<<endl; */

  if (argc != 2) {
    cout << "example_1 takes only one argument" << endl;
    cout << "usage: example_1 num_threads" << endl;
    exit(0);
  }

  int thread_count = atoi(argv[1]);
  cout << "thread count=" << thread_count << endl;
#pragma omp parallel num_threads(thread_count)
  Hello();
  return 0;
}
void Hello() {
  int my_rank = omp_get_thread_num();
  int thread_count = omp_get_num_threads();
  cout << "Hello from thread " << my_rank << endl
       << "Thread count=" << thread_count << endl;
}
