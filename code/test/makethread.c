#include "syscall.h"

void test(void* c) {
    char d = (char) c;
    PutChar(d);
}

int main() {
    int char_thread;
    char_thread = ThreadCreate(test, (void *) 'a');
    while(42) {};
}
