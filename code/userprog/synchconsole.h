#include "console.h"

#ifdef CHANGED
  #ifndef SYNCHCONSOLE_H

    #define SYNCHCONSOLE_H

    #include "copyright.h"
    #include "utility.h"
    #include "console.h"
    #include "syscall.h"
    #include "synch.h"

    class SynchConsole:dontcopythis {
      public:
        Lock * print_lock;
        SynchConsole(const char *readFile, const char *writeFile);
        // initialize the hardware console device
        ~SynchConsole();                    // clean up console emulation
        void SynchPutChar(int ch);          // Unix putchar(3S)
        int SynchGetChar();                 // Unix getchar(3S)
        void SynchPutString(const char *s); // Unix fputs(3S)
        int SynchGetString(char *s, int n);       // Unix fgets(3S)
      private:
        Lock *read_lock;
        Lock *write_lock;
        Console *console;
    };
  #endif // SYNCHCONSOLE_H
#endif // CHANGED
