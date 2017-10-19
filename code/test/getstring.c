#include "syscall.h"

int main();

int main()
{
  int maxsize = 19;
  char string[maxsize];
  printf("Saisissez une chaîne (%d caractères max)\n", maxsize);
  GetString(string, maxsize);
  PutString("\nEst-ce que c'était : \n<< ");
  PutString(string);
  PutString(" >> ?\n");
  Halt();
  return 0;
}
