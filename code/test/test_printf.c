#include "syscall.h"

int main();

int main() {
    int n;
    const char * chaine = "abcd";
    // printf("Bonjour. Ceci est un long message, qui contiendra des paramètres. Par exemple, ceci est un paramètre : %s. Ceci également : %s. Ce qui est impressionant, c'est qu'on peut avoir jusqu'à %d nombres inclus. Ou même %d. En fait, vous choisissez. C'est le futur, c'est maintenant. Votez %s", "heyey", "hooo", 0, -1, "Françis. Ou Marc. En somme, votez pour moi.\n\n");
    n = printf("%s", chaine);
    printf("\n\nLa longueur de la précédente chaîne (<%s>) est : %d caractères\n", chaine, n);
    Halt();
    return 1;
}
