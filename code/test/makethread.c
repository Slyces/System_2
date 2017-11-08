#include "syscall.h"

void afficheChar(void* c) {
    char d = (char) c;
    PutChar(d);
    ThreadExit();
}

void afficheString(char* c) {

    PutString((char*)c);
    ThreadExit();
}

int main() {
    //PutString("ceci est el main1");

    // premier thread
    //int char_thread;
    void * func = afficheChar;
    int char_thread = ThreadCreate(func, (void *) 'a');

    // main
    PutString("ceci el main.\n");

    //Secon thread
    func = afficheString;
    char_thread = ThreadCreate(func, "coucou c'est nous");


    // main
    PutString("el main. fin\n");
    while (1) {
    }
    return 0;
  }
