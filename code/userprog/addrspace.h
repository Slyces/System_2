// addrspace.h
//      Data structures to keep track of executing user programs
//      (address spaces).
//
//      For now, we don't keep any information about address spaces.
//      The user level CPU state is saved and restored in the thread
//      executing the user program (see thread.h).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#ifndef ADDRSPACE_H
#define ADDRSPACE_H

#include "copyright.h"
#include "filesys.h"
#include "translate.h"
#include "bitmap.h"

class Lock;
class Condition;

#ifdef CHANGED
#define ThreadStackSize 256
#define UserStacksAreaSize  (ThreadStackSize * 16)	// increase this as necessary!
#endif //CHANGED

class AddrSpace:dontcopythis
{
  public:
    AddrSpace (OpenFile * executable);	// Create an address space,
    // initializing it with the program
    // stored in the file "executable"
    ~AddrSpace ();		// De-allocate an address space

    void InitRegisters ();	// Initialize user-level CPU registers,
    // before jumping to user code

    void SaveState ();		// Save/restore address space-specific
    void RestoreState ();	// info on a context switch

    #ifdef CHANGED
    int AllocateUserStack(int slot);
    int RequestStackSlot(bool waiting);
    void ReleaseStackSlot(int slot);
    bool IsLastThread();
    #endif //CHANGED

  private:
      TranslationEntry * pageTable;	// Assume linear page table translation
    // for now!
    unsigned int numPages;	// Number of pages in the virtual
    // address space

  #ifdef CHANGED
    BitMap * stackBitMap;
    Lock * bitMapLock;
    Condition * slotCondition;
    int threadNumber;
  #endif
};

#endif // ADDRSPACE_H
