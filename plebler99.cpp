#include <omp.h>

#include <iostream>

int main(int argc, char *argv[]) {
  int list_length = 100;
  int a[100];
  int tmp;

  for (int i = 0; i < list_length; i++) {
    for (int j = 0; j < list_length - 1; j++) {
      if (a[j] > a[j + 1]) {
        tmp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = tmp;
      }
    }
  }

  for (int phase = 0; phase < list_length; phase++) {
    if (phase % 2 == 0) {
      for (int j = 0; j < list_length - 1; j++) {
        if (a[j] > a[j + 1]) {
          tmp = a[j];
          a[j] = a[j + 1];
          a[j + 1] = tmp;
        }
      }
    } else {
      for (int j = 0; j < list_length - 1; j++) {
        if (a[j + 1] > a[j + 2]) {
          tmp = a[j + 1];
          a[j] = a[j + 2];
          a[j + 2] = tmp;
        }
      }
    }
  }
}
