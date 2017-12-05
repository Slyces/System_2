#ifdef CHANGED
# include "userthread.h"



struct schmurtz {
    int f_adress;
    int arg_adress;
    int exit_adress;
};

static void StartUserThread(void* schmurtz) {
    DEBUG('s', "StartUserThread\n");
    int i;

    struct schmurtz *new_schmurtz = (struct schmurtz *) schmurtz;

    for (i = 0; i < NumTotalRegs; i++) machine->WriteRegister(i, 0);

    // Initial program counter -- must be location of "Start"
    DEBUG('x', "Writing function adress : 0x%x to PCReg\n", new_schmurtz->f_adress);
    machine->WriteRegister(PCReg, new_schmurtz->f_adress);

    // Need to also tell MIPS where next instruction is, because
    // of branch delay possibility
    machine->WriteRegister(NextPCReg, machine->ReadRegister(PCReg) + 4);
    //machine->WriteRegister(NextPCReg, new_schmurtz->f_adress + 4);

    DEBUG('x', "Writing arg adress : 0x%x to register 4\n", new_schmurtz->arg_adress);
    machine->WriteRegister(4, new_schmurtz->arg_adress);
    DEBUG('x', "Successfully wrote\n");

    DEBUG('x', "Writing exit adress : 0x%x to register 31\n", new_schmurtz->exit_adress);
    machine->WriteRegister(31, new_schmurtz->exit_adress);

    delete new_schmurtz;

    // Set the stack register to the end of the address space, where we
    // allocated the stack; but subtract off a bit, to make sure we don't
    // accidentally reference off the end!

    DEBUG('x', "Allocating stack\n");

    int userStackPtr = currentThread->space->AllocateUserStack(currentThread->getSlot());
    DEBUG('x', "Writing stack pointer to register\n");
    machine->WriteRegister(StackReg, userStackPtr);
    DEBUG('x', "Initializing stack register to 0x%x\n", userStackPtr);

    machine->Run();
}

int
do_ThreadCreate(int f, int arg, int exit_adress) {
    DEBUG('s', "do Thread Create\n");
    // When no space available, return -1
    struct schmurtz * container = new struct schmurtz;

    Thread *newThread = new Thread("New Thread");

    int slot = newThread->space->RequestStackSlot(false);
    // Not waiting
    if (slot == -1) {
        DEBUG('s', "No slot available\n");
        return -1;
    }
    newThread->setSlot(slot);
    DEBUG('s', "Selected slot %d\n", slot);

    container->f_adress   = f;
    container->arg_adress = arg;
    container->exit_adress = exit_adress;

    newThread->Start((VoidFunctionPtr) StartUserThread, (void*) container);
    // currentThread->Yield();
    return 0;
}

int
do_WaitingThreadCreate(int f, int arg, int exit_adress) {
    DEBUG('s', "do Waiting Thread Create\n");
    struct schmurtz * container = new struct schmurtz;

    Thread *newThread = new Thread("New Thread");

    int slot = newThread->space->RequestStackSlot(true);
    // true = waiting
    // May wait if no slot is available. Always has a slot when reaching here
    newThread->setSlot(slot);
    DEBUG('s', "Selected slot %d\n", slot);

    container->f_adress   = f;
    container->arg_adress = arg;
    container->exit_adress = exit_adress;

    newThread->Start((VoidFunctionPtr) StartUserThread, (void*) container);
    // currentThread->Yield();
    return 0;
}

int do_ThreadExit() {
    DEBUG('s', "ThreadExit\n");
    if(currentThread->space->IsLastThread())
        interrupt->Halt();

    int slot = currentThread->getSlot();
    DEBUG('s', "Exiting the thread at slot %d\n", slot);
    currentThread->space->ReleaseStackSlot(slot);
    currentThread->Finish();
    // On ne sait pas si d'autres threads utilisent cet espace d'adressage
    return 1;
}

void
startUserProcess(int f) {
  currentThread->space->InitRegisters(); // set the initial register values
  currentThread->space->RestoreState();
  machine->Run();
}
#endif //CHANGED
