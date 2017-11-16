#include "syscall.h"

// int[] produits = new int[100];

// void producteur(void* array) {
//     int id = ((int*) array)[0];
//     sem_t sem_prod = (sem_t) ((int *) array)[1];
//
//     // ThreadExit();
// }
//
// void consommateur(void* array) {
//     int id = ((int*) array)[0];
//     sem_t sem_cons = (sem_t) ((int *) array)[1];
//
//     // ThreadExit();
// }

int main() {
    // int char_thread, i;
    // int n_prod = 5;
    // int n_cons = 5;
    // int array_prod[n_prod][2];
    // int array_cons[n_cons][2];
    //
    // sem_t sem_prod = NewSemaphore("Semaphore producteur", 1);
    // sem_t sem_cons = NewSemaphore("Semaphore consommateur", 0);
    //
    // for(i = 0; i < n_prod; i++) {
    //   array_prod[i][0] = i + 1;
    // }
    //
    // for(i = 0; i < n_cons; i++) {
    //   array_cons[i][0] = n_prod + 1 + i;
    // }
    //
    // for (i = 0; i < n_prod; i++) {
    //   char_thread = WaitingThreadCreate(producteur, array_prod[i]);
    // }
    //
    // for (i = 0; i < n_cons; i++) {
    //   char_thread = WaitingThreadCreate(consommateur, array_cons[i]);
    // }
    // // ThreadExit();
    // // Halt();
    return 1;
}
