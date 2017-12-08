#include "syscall.h"
#define THIS "a2a2a2"
#define THAT "b2b2b2"

const int N = 10;

void puts(const char *s) {
        const char * p;
        for (p = s; *p != '\0'; p++) {
                PutChar(*p);
        }
}

void f(void *arg) {
        const char *s = arg;
        int i;
        for (i = 0; i < N; i++) {
                puts(s);
                ThreadExit();
        }
}

int main()
{
        int i;
        for (i = 0; i < 5; i++) {
                ThreadCreate(f, THIS);
        }
        f(THAT);
        ThreadExit();
        return 1;
}
