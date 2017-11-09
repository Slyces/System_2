#include "syscall.h"

void thread_test(void* array) {
    int id = ((int*) array)[0];
    int i, n = 5;

    PutString("_[Thread start]_");

    for (i = 0; i < n; i++) {
      /* code */
      // PutChar('0' + id);
      PutChar('+');
    }

    PutString("_[Thread middle]_");

    for (i = 0; i < n; i++) {
      /* code */
      // PutChar('0' + id);
      PutChar('+');
    }

    PutString("_[Thread end]_");

    ThreadExit();
}

int main() {
    int char_thread, i;
    int n = 9;
    int array[n][1];
    for(i = 0; i < n; i++) {
      array[i][0] = i + 1;
    }

    PutString(">> Main :: pre-creation\n\n");
    for (i = 0; i < n; i++) {
      char_thread = ThreadCreate(thread_test, array[i]);
    }
    PutString("\n\n>> Main :: post-creation\n\n");
    // PutString(">> Main :: random dashes ---------------------------------------------------------------------------\n");
    ThreadExit();
    return 1;
}
