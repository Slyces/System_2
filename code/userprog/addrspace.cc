// addrspace.cc

//      Routines to manage address spaces (executing user programs).
//
//      In order to run a user program, you must:
//
//      1. link with the -N -T 0 option
//      2. run coff2noff to convert the object file to Nachos format
//              (Nachos object code format is essentially just a simpler
//              version of the UNIX executable object code format)
//      3. load the NOFF file into the Nachos file system
//              (if you haven't implemented the file system yet, you
//              don't need to do this last step)
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "addrspace.h"
#include "noff.h"
#include "syscall.h"
#include "new"

// ----------------------------------------------------------------------
// SwapHeader
//      Do little endian to big endian conversion on the bytes in the
//      object file header, in case the file was generated on a little
//      endian machine, and we're now running on a big endian machine.
// ----------------------------------------------------------------------

static void
SwapHeader(NoffHeader *noffH)
{
    noffH->noffMagic              = WordToHost(noffH->noffMagic);
    noffH->code.size              = WordToHost(noffH->code.size);
    noffH->code.virtualAddr       = WordToHost(noffH->code.virtualAddr);
    noffH->code.inFileAddr        = WordToHost(noffH->code.inFileAddr);
    noffH->initData.size          = WordToHost(noffH->initData.size);
    noffH->initData.virtualAddr   = WordToHost(noffH->initData.virtualAddr);
    noffH->initData.inFileAddr    = WordToHost(noffH->initData.inFileAddr);
    noffH->uninitData.size        = WordToHost(noffH->uninitData.size);
    noffH->uninitData.virtualAddr =
        WordToHost(noffH->uninitData.virtualAddr);
    noffH->uninitData.inFileAddr = WordToHost(noffH->uninitData.inFileAddr);
}

// ----------------------------------------------------------------------
// AddrSpace::AddrSpace
//      Create an address space to run a user program.
//      Load the program from a file "executable", and set everything
//      up so that we can start executing user instructions.
//
//      Assumes that the object code file is in NOFF format.
//
//      First, set up the translation from program memory to physical
//      memory.  For now, this is really simple (1:1), since we are
//      only uniprogramming, and we have a single unsegmented page table
//
//      "executable" is the file containing the object code to load into memory
// ----------------------------------------------------------------------

AddrSpace::AddrSpace(OpenFile *executable)
{
    NoffHeader   noffH;
    unsigned int i, size;

  #if CHANGED
    threadNumber = 0;
    bitMapLock = new Lock("UserStack's Bit Map Lock");
    slotCondition = new Condition("Condition Lock for threads waiting a free slot");
    int max_slot_number = UserStacksAreaSize / ThreadStackSize;
    stackBitMap = new BitMap(max_slot_number);
    stackBitMap->Mark(0); // Il existe au moins 1 thread : le main.
  #endif //CHANGED

    executable->ReadAt(&noffH, sizeof(noffH), 0);

    if ((noffH.noffMagic != NOFFMAGIC) &&
        (WordToHost(noffH.noffMagic) == NOFFMAGIC)) SwapHeader(&noffH);

    /* Check that this is really a MIPS program */
    ASSERT(noffH.noffMagic == NOFFMAGIC);

    // how big is address space?
    size = noffH.code.size + noffH.initData.size + noffH.uninitData.size +
           UserStacksAreaSize; // we need to increase the size
    // to leave room for the stack
    numPages = divRoundUp(size, PageSize);
    size     = numPages * PageSize;

    // check we're not trying
    // to run anything too big --
    // at least until we have
    // virtual memory
    if (numPages > NumPhysPages) throw std::bad_alloc();

    DEBUG('a', "Initializing address space, num pages %d, total size 0x%x\n",
          numPages, size);

    // first, set up the translation
    pageTable = new TranslationEntry[numPages];

    for (i = 0; i < numPages; i++)
    {
        pageTable[i].physicalPage = i; // for now, phys page # = virtual page #
        pageTable[i].valid        = TRUE;
        pageTable[i].use          = FALSE;
        pageTable[i].dirty        = FALSE;
        pageTable[i].readOnly     = FALSE; // if the code segment was entirely
                                           // on
        // a separate page, we could set its
        // pages to be read-only
    }

    // then, copy in the code and data segments into memory
    if (noffH.code.size > 0)
    {
        DEBUG('a', "Initializing code segment, at 0x%x, size 0x%x\n",
              noffH.code.virtualAddr, noffH.code.size);
        executable->ReadAt(&(machine->mainMemory[noffH.code.virtualAddr]),
                           noffH.code.size, noffH.code.inFileAddr);
    }

    if (noffH.initData.size > 0)
    {
        DEBUG('a', "Initializing data segment, at 0x%x, size 0x%x\n",
              noffH.initData.virtualAddr, noffH.initData.size);
        executable->ReadAt(&
                           (machine->mainMemory
                            [noffH.initData.virtualAddr]),
                           noffH.initData.size, noffH.initData.inFileAddr);
    }

    DEBUG('a', "Area for stacks at 0x%x, size 0x%x\n",
          size - UserStacksAreaSize, UserStacksAreaSize);

    pageTable[0].valid = FALSE; // Catch NULL dereference
}

// ----------------------------------------------------------------------
// AddrSpace::~AddrSpace
//      Dealloate an address space.  Nothing for now!
// ----------------------------------------------------------------------

AddrSpace::~AddrSpace()
{
    // LB: Missing [] for delete
    // delete pageTable;
    delete[] pageTable;

    // End of modification
    #ifdef CHANGED
    delete stackBitMap;
    delete bitMapLock;
    delete slotCondition;
    #endif
}

// ----------------------------------------------------------------------
// AddrSpace::InitRegisters
//      Set the initial values for the user-level register set.
//
//      We write these directly into the "machine" registers, so
//      that we can immediately jump to user code.  Note that these
//      will be saved/restored into the currentThread->userRegisters
//      when this thread is context switched out.
// ----------------------------------------------------------------------

void
AddrSpace::InitRegisters()
{
    int i;

    for (i = 0; i < NumTotalRegs; i++) machine->WriteRegister(i, 0);

    // Initial program counter -- must be location of "Start"
    machine->WriteRegister(PCReg, USER_START_ADDRESS);

    // Need to also tell MIPS where next instruction is, because
    // of branch delay possibility
    machine->WriteRegister(NextPCReg, machine->ReadRegister(PCReg) + 4);

    // Set the stack register to the end of the address space, where we
    // allocated the stack; but subtract off a bit, to make sure we don't
    // accidentally reference off the end!
    machine->WriteRegister(StackReg, numPages * PageSize - 16);
    DEBUG('a', "Initializing stack register to 0x%x\n",
          numPages * PageSize - 16);
}

// ----------------------------------------------------------------------
// AddrSpace::SaveState
//      On a context switch, save any machine state, specific
//      to this address space, that needs saving.
//
//      For now, nothing!
// ----------------------------------------------------------------------

void
AddrSpace::SaveState()
{}

// ----------------------------------------------------------------------
// AddrSpace::RestoreState
//      On a context switch, restore the machine state so that
//      this address space can run.
//
//      For now, tell the machine where to find the page table.
// ----------------------------------------------------------------------

void
AddrSpace::RestoreState()
{
    machine->pageTable     = pageTable;
    machine->pageTableSize = numPages;
}

/* ======================================================================
 * Action 1.4
 * ====================================================================== */
 #ifdef CHANGED
int
AddrSpace::AllocateUserStack(int slot) {
    // les threads ont un slot_number > 0
    return numPages * PageSize - slot * ThreadStackSize - 16;
}
#endif //CHANGED

/* ======================================================================
 * Action 2.4
 * ====================================================================== */

// Renvoie -1 si il n'y a pas d'emplacement disponible.
int
AddrSpace::RequestStackSlot(bool waiting)
{
    bitMapLock->Acquire();
    // Section critique pour garantir 1 seul thread par emplacement

    int freeSlot;
    while ((freeSlot = stackBitMap->Find()) == -1) {
      // Find retourne -1 quand tous les bits sont marqués
      if (!waiting) {
        bitMapLock->Release();
        return -1;
      } else slotCondition->Wait(bitMapLock);
    }
    DEBUG('z', "Acquiring slot number : %d\n", freeSlot);
    stackBitMap->Mark(freeSlot);
    threadNumber++;
    bitMapLock->Release();
    return freeSlot;
}

void
AddrSpace::ReleaseStackSlot(int slot)
{
    bitMapLock->Acquire();
    DEBUG('s', "Releasing on bit %d", slot);
    stackBitMap->Clear(slot);
    threadNumber--;
    slotCondition->Signal(bitMapLock);
    bitMapLock->Release();
}

bool
AddrSpace::IsLastThread()
{
  bitMapLock->Acquire();
  int n = threadNumber;
  bitMapLock->Release();
  return n == 0;
}
