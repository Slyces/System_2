#include "syscall.h"

void
thread_test(void* array) {
    int id = ((int*) array)[0];
    volatile int i;
    int n = 10;

    for (i = 0; i < n; i++) {
      PutChar('a' + id - 1);
    }

    // ThreadExit();
}

int
main() {
    int char_thread, i;
    int n = 26;
    int array[n][1];
    for(i = 0; i < n; i++) {
      array[i][0] = i + 1;
    }

    for (i = 0; i < n; i++) {
      char_thread = WaitingThreadCreate(thread_test, array[i]);
    }
    // ThreadExit();
    // Halt();
    return 1;
}
