#ifdef CHANGED
# include "userthread.h"

struct schmurtz {
    int f_adress;
    int arg_adress;
};

static void StartUserThread(void* schmurtz) {
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

    delete new_schmurtz;

    // Set the stack register to the end of the address space, where we
    // allocated the stack; but subtract off a bit, to make sure we don't
    // accidentally reference off the end!
    DEBUG('x', "Allocating stack\n");
    int userStackPtr = currentThread->space->AllocateUserStack();
    DEBUG('x', "Writing stack pointer to register\n");
    machine->WriteRegister(StackReg, userStackPtr);
    DEBUG('x', "Initializing stack register to 0x%x\n", userStackPtr);

    machine->Run();
}

int do_ThreadCreate(int f, int arg) {
    struct schmurtz * container = new struct schmurtz;
    Thread *newThread = new Thread("New Thread");

    container->f_adress   = f;
    container->arg_adress = arg;

    newThread->Start((VoidFunctionPtr) StartUserThread, (void*) container);
    return 1;
}

int do_ThreadExit() {
  currentThread->Finish();
  // On ne sait pas si d'autres threads utilisent cet espace d'adressage
  return 1;
}


#endif //CHANGED
