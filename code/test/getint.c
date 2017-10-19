#include "syscall.h"

int main()
{
    // char test[4];
    int test[1];
    PutString("Test de GetInt (syscall).\n");
    GetInt((int *) test);
    PutString("La valeur de l'entier est : ");
    // PutInt((char *) *test);
    PutInt(*test);
    PutString(".\n");

    // DeallocBoundedArray(test);
    Halt();
    return 1;
}
