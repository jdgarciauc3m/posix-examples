#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void print_args(int argc, char *argv[]) {
  printf("Number of arguments: %d\n", argc);
  for (int i = 0; i < argc; i++) {
    printf("Argument %d: %s\n", i, argv[i]);
  }
}

int run_program(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Error: No program specified.\n");
    fprintf(stderr, "Usage: %s <program> [args...]\n", argv[0]);
    return EXIT_FAILURE;
  }

  pid_t pid = fork();
  switch (pid) {
  case -1:
    perror("fork");
    return EXIT_FAILURE;
  case 0: // Child process
  {
    execvp(argv[1], &argv[1]);
    // If execvp returns, it means there was an error
    perror("execvp");
    return EXIT_FAILURE;
  }
  default:
    printf("Parent process\n");
  }
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  print_args(argc, argv);
  return run_program(argc, argv);
}