// system.h

//      All global variables used in Nachos are defined here.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#ifndef SYSTEM_H
#define SYSTEM_H

#include "copyright.h"
#include "utility.h"
#include "thread.h"
#include "scheduler.h"
#include "interrupt.h"
#include "stats.h"
#include "timer.h"

// Initialization and cleanup routines
extern void Initialize(int    argc,
                       char **argv); // Initialization,
                                     // called before anything else
extern void Cleanup();               // Cleanup, called when
// Nachos is done.

extern Thread *currentThread;        // the thread holding the CPU
extern Thread *threadToBeDestroyed;  // the thread that just finished
extern Scheduler  *scheduler;        // the ready list
extern Interrupt  *interrupt;        // interrupt status
extern Statistics *stats;            // performance metrics
extern Timer *timer;                 // the hardware alarm clock

#ifdef USER_PROGRAM

# include "machine.h"
extern Machine *machine; // user program memory and registers


# ifdef CHANGED

// Gestion des sémaphores
#include "usersemaphores.h"
#include "synch.h"
extern Semaphore * threads_mutex;
extern UserSemaphore * user_semaphores;

// Gestion des processus
extern Lock * processLock;
extern int nb_process;

# include "pageprovider.h"
extern PageProvider *pageprovider;

int copyStringFromMachine(int      from,
                          char    *to,
                          unsigned size);
int copyStringToMachine(char        *from,
                        unsigned int to,
                        int          size);

// #  define MAX_STRING_SIZE 32
#  define MAX_STRING_SIZE 10
#  include "synchconsole.h"
#  include "synch.h"
extern SynchConsole *synchconsole; // synchconsole
extern Semaphore    *char_stack_lock;
# endif // ifdef CHANGED

#endif // ifdef USER_PROGRAM

#ifdef FILESYS_NEEDED // FILESYS or FILESYS_STUB
# include "filesys.h"
extern FileSystem *fileSystem;
#endif // ifdef FILESYS_NEEDED

#ifdef FILESYS
# include "synchdisk.h"
extern SynchDisk *synchDisk;
#endif // ifdef FILESYS

#ifdef NETWORK
# include "post.h"
extern PostOffice *postOffice;
#endif // ifdef NETWORK

#endif // SYSTEM_H
