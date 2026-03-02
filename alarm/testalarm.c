#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_alarm(int signal_id) {
  (void)signal_id; // Unused parameter
  printf("Alarm received!\n");
}

int main(void) {
  struct sigaction action;
  action.sa_handler = handle_alarm;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  sigaction(SIGALRM, &action, NULL);

  // action.sa_handler = SIG_IGN; // Ignore SIGINT
  // sigaction(SIGINT, &action, NULL);

  for (;; ) {
    alarm(3);
    pause();;
  }
  printf("Finalizing...\n");
  return 0;
}
