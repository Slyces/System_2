#include "syscall.h"

int main();

int main() {
    char * string[100];
    sprintf(string, "Phrase aléatoire contenant %s mots et des chiffres : %d %d %d %d.\n", "des", 83, 2, 7, 24);
    PutString(string);
    Halt();
    return 1;
}
