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
    PutString("le retour d' el main.");

    //Secon thread
    func = afficheString;
    char_thread = ThreadCreate(func, "coucou c'est nous");

    // main
    PutString("ceci est el main. fin");

    return 0;
  }
