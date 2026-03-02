#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t pid;

void handle_alarm(int signal_id) {
  (void)signal_id; // Unused parameter
  kill(pid, SIGKILL);
} 

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
    return 1;
  } 
  char ** args = argv + 1;
  pid = fork();
  switch (pid) {
    case -1:
      perror("fork");
      return 1;
    case 0:
      execvp(args[0], args);
      perror("exec");
      return -1;
    default:
    {
      struct sigaction action;
      action.sa_handler = handle_alarm;
      sigemptyset(&action.sa_mask);
      action.sa_flags = 0;
      sigaction(SIGALRM, &action, NULL);
      alarm(5);
      int status;
      wait(&status);
      printf("Child process finished with status %d\n", status);
    }
  }
  return 0;
}
