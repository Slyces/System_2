#include "syscall.h"

int main();

int main() {
    int n;
    printf("Bonjour. Ceci est un long message, qui contiendra des paramètres. Par exemple, ceci est un paramètre : %s. Ceci également : %s. Ce qui est impressionant, c'est qu'on peut avoir jusqu'à %d nombres inclus. Ou même %d. En fait, vous choisissez. C'est le futur, c'est maintenant. Votez %s", "heyey", "hooo", 0, -1, "Françis. Ou Marc. En somme, votez pour moi.\n\n");
    n = printf("abcd");
    printf("\n\nLa longueur de la précédente chaîne (<abcd>) est : %d caractères\n", n);
    Halt();
    return 1;
}
