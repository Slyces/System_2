#include "syscall.h"

void thread_test(void* array) {
    int id = ((int*) array)[0];
    char c = (char)((int*) array)[1];
    int n = ((int*) array)[2];
    int i;

    // PutInt(id);
    // PutChar(c);

    // printf(">> Thread %d :: Entering\n", id);
    printf("[%d|", id);
    for (i = 0; i < n; i++) {
      /* code */
      // PutChar(c + i);
    }
    printf("|%d]", id);
    // Thread::ThreadExit();
    // PutString(">> Thread :: Exiting\n");
    ThreadExit();
}

int main() {
    int char_thread, i;
    int n = 3;
    int array[n][3];
    for(i = 0; i < n; i++) {
      array[i][0] = i + 1;
      array[i][2] = 10;
    }
    array[0][1] = 'a';
    array[1][1] = 'A';
    array[2][1] = '0';

    PutString(">> Main :: pre-creation\n");
    for (i = 0; i < n; i++) {
      char_thread = ThreadCreate(thread_test, array[i]);
    }
    PutString(">> Main :: post-creation\n");
    ThreadExit();
    return 1;
}
