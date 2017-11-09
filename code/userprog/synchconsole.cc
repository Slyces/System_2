#ifdef CHANGED
  #include "copyright.h"
  #include "system.h"
  #include "synchconsole.h"
  #include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;

static void ReadAvailHandler(void *arg) {
    (void)arg; readAvail->V();
}

static void WriteDoneHandler(void *arg) {
    (void)arg; writeDone->V();
}

SynchConsole::SynchConsole(const char *in, const char *out) {
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    console   = new Console(in, out, ReadAvailHandler, WriteDoneHandler, 0);
    read_lock = new Lock("read lock");
    write_lock = new Lock("write lock");


    print_lock = new Lock("print lock");
}

SynchConsole::~SynchConsole() {
    delete console;
    delete writeDone;
    delete readAvail;
    delete read_lock;
    delete write_lock;


    delete print_lock;
}

void SynchConsole::SynchPutChar(int ch) {
    write_lock->Acquire();
    console->PutChar(ch);
    writeDone->P();
    write_lock->Release();
}

int SynchConsole::SynchGetChar() {
    char c;

    read_lock->Acquire();

    readAvail->P(); // wait for character to arrive
    c = console->GetChar();

    read_lock->Release();
    return c;
}

void SynchConsole::SynchPutString(const char *s) {
    write_lock->Acquire();
    int i = 0;

    while (s[i] != '\0') {
        SynchPutChar(s[i]);
        i++;
    }
    write_lock->Release();
}

  #if 1
int SynchConsole::SynchGetString(char *s, int n) {
    // n is the total size, including 1 byte for the \0, so at most n - 1 chars
    // can be obtained
    int  i = 0;
    char c;

    if (n == 1) { s[0] = '\0'; return 0; } // case of empty call (1 byte only
                                           // for \0)
    read_lock->Acquire();
    do {
        c = SynchGetChar();

        switch (c) {
        case '\n': // if \n, stop right away
            s[i]     = '\n';
            s[i + 1] = '\0';
            return i;

        case EOF:
            s[i] = '\0';
            return i;

        default:
            s[i] = c;
            i++;
        } // on garde 1 caractère pour le \0.
    } while (i < n - 1);
    s[i] = '\0'; // last instruction was i++, so the \0 is at s[n-1], n'th char

    read_lock->Release();

    return i + 1; // when exiting this way (full string, still things to read),
                  // we count the \0. and send back n instead of at most n - 1
}

  #endif // if 0
#endif   // CHANGED
