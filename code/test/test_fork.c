# include "syscall.h"

int main() {
  printf("This is main talking\n");

  printf("\nMain forkexecs\n");
  ForkExec("../test/putchar");
  printf("\nMain forkexecs\n");
  ForkExec("../test/putchar");
  return 1;
}
