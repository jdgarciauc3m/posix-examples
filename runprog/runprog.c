#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void print_args(int argc, char *argv[]) {
  printf("Number of arguments: %d\n", argc);
  for (int i = 0; i < argc; i++) {
    printf("Argument %d: %s\n", i, argv[i]);
  }
}

void run_program(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Error: No program specified.\n");
    fprintf(stderr, "Usage: %s <program> [args...]\n", argv[0]);
    return;
  }

  pid_t pid = fork();
  switch (pid) {
  case -1:
    fprintf(stderr, "Error: Failed to fork process.\n");
    return;
  case 0: // Child process
  {
    execvp(argv[1], &argv[1]);
    // If execvp returns, it means there was an error
    perror("execvp");
    break;
  }
  default:
    printf("Parent process\n");
  }
}

int main(int argc, char *argv[]) {
  print_args(argc, argv);
  run_program(argc, argv);
  return 0;
}