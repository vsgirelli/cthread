#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>

int main() {
  int error = cjoin(2);
  printf("error: %d", error);
  return 0;
}
