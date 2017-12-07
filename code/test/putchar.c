#include "syscall.h"

void print(char c, int n)
{
      int i;
       #if 1
        for (i = 0; i < n; i++) {
                PutChar(c + i);
        }
        PutChar('\n');
       #endif
}

int main()
{
        PutString("\nI am putchar and I'm usefull\n");
        print('a', 5);
        PutString("\nI am putchar and I'm out\n");
        // Halt();
}
