#include "syscall.h"

int main()
{
    char c;
    int i;
    printf("Entrez 8 caractères (entrée compte comme 1).\n");
    for(i = 0; i < 8; i++) {
      c = GetChar();
      PutChar(c);
    }
    PutChar('\n');
    Halt();
}
