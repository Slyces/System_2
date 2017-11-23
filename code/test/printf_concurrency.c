#include "syscall.h"

void thread_test(void* array) {
        int id = ((int*) array)[0];
        int i, j = 0, n = 20000;
        char * format = "        | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s |\n";

        printf(format,
               id == 0 ? "+" : " ",
               id == 1 ? "+" : " ",
               id == 2 ? "+" : " ",
               id == 3 ? "+" : " ",
               id == 4 ? "+" : " ",
               id == 5 ? "+" : " ",
               id == 6 ? "+" : " ",
               id == 7 ? "+" : " ",
               id == 8 ? "+" : " ",
               id == 9 ? "+" : " ");

        for(i = 0; i < n; i++) {
                j = i - j + 247;
        }

        printf(format,
               id == 0 ? "-" : " ",
               id == 1 ? "-" : " ",
               id == 2 ? "-" : " ",
               id == 3 ? "-" : " ",
               id == 4 ? "-" : " ",
               id == 5 ? "-" : " ",
               id == 6 ? "-" : " ",
               id == 7 ? "-" : " ",
               id == 8 ? "-" : " ",
               id == 9 ? "-" : " ");

}

int main() {
        int char_thread, i;
        int n = 10;
        int array[n][1];
        for(i = 0; i < n; i++) {
                array[i][0] = i;
        }

        printf("Threads | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |\n");

        for (i = 0; i < n; i++) {
                char_thread = ThreadCreate(thread_test, array[i]);
        }
        return 1;
}
