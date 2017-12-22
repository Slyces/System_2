#ifndef USERTHREAD_H
#define USERTHREAD_H
#include "thread.h"
#include "system.h"

class Semaphore;

extern int do_ThreadCreate(int f, int arg, int exit_adress);
extern int do_WaitingThreadCreate(int f, int arg, int exit_adress);
extern int do_ThreadExit();
extern void do_Exit();
extern void startUserProcess(void *);
#endif // USERTHREAD_H
