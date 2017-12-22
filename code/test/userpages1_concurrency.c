#include "syscall.h"


void f(void *array) {
        int id = ((int*) array)[0];
        int i, n = 10;
        printf("this is Thread number  %d on process 1\n",id );
        //ThreadExit();
}

int main()
{
        int i;
        int n = 5;
        int array[n][1];
        for(i = 0; i < n; i++) {
                array[i][0] = i;
        }
        for (i = 0; i < n; i++) {
                ThreadCreate(f, array[i]);
        }
        return 1;
}
