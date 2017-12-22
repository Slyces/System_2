#include "syscall.h"

void
create_sem(void * ignored) {
        int i, j = 0;
        sem_t semaphore;
        semaphore = NewSemaphore("Some Sem", 1);
        // printf("Created %d\n", semaphore);
        for (i = 0; i < 200; i++) {
                j++;
                // PutChar(' ');
                // P(semaphore);
                // V(semaphore);
        }
        DeleteSemaphore(semaphore);
        // printf("Deleted %d\n", semaphore);
        return;
}

int
main() {
        int i;
        for (i = 0; i < 3; i++) {
                WaitingThreadCreate(create_sem, 0);
        }
        return 1;
}
