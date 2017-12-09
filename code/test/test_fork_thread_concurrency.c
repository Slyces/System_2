# include "syscall.h"

int main() {
        int i;
        printf("This is main talking\n");
        for (i = 0; i < 12; i++) {
                ForkExec("../test/userpages1_concurrency");
                ForkExec("../test/userpages2_concurrency");
        }
        return 1;
}
