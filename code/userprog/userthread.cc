# include "userthread.h"

int do_ThreadCreate(int f, int arg) {
    Thread *newThread = new Thread ("NewThread");
    newThread->Start(StartUserThread, schmurtz);
}
