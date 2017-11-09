#include "syscall.h"

void thread_test(void* array) {
    int id = ((int*) array)[0];
    char c = (char)((int*) array)[1];
    int n = ((int*) array)[2];
    int i;
    PutString(">> Thread :: Entering thread\n");
    for (i = 0; i < n; i++) {
      /* code */
      PutChar(c + i);
    }
    PutString("\n");
    // Thread::ThreadExit();
    PutString(">> Thread :: Exiting thread\n");
    ThreadExit();
}

int main() {
    int char_thread, i;
    int array[2][3];
    for(i = 0; i < 2; i++) {
      array[i][0] = i + 1;
      array[i][2] = 26;
    }
    array[0][1] = 'a';
    array[1][1] = 'A';

    printf(">> Main :: pre-creation\n");
    for (i = 0; i < 2; i++) {
      char_thread = ThreadCreate(thread_test, array[i]);
    }
    printf(">> Main :: post-creation\n");
    printf(">> Main :: random dashes ---------------------------------------------------------------------------\n");
    ThreadExit();
    return 1;
}
