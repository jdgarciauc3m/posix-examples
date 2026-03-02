#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handle_signal(int signal_id) {
  fprintf(stderr, "Signal handler called with signal: %d\n", signal_id);
  fprintf(stderr, "Illegal memory access detected.\n");
  exit(-1);
  //signal(signal_id, SIG_DFL);
}

int main(void) {
  signal(SIGSEGV, handle_signal);
  printf("Signal setup complete. Triggering segmentation fault...\n");
  int *ptr = NULL;
  *ptr = 42; // This will cause a segmentation fault
  printf("Hello, World!\n");
  *ptr = 99;
  return 0;
}
