#ifndef PAGEPROVIDER_H
#define PAGEPROVIDER_H

#ifdef CHANGED
// #include "synch.h"
#include "addrspace.h"
// #include "system.h"

class BitMap;
class Lock;

class PageProvider {
public:
  PageProvider();
  ~PageProvider();

  int GetEmptyPage();
  void ReleasePage(int busy);
  int NumAvailPage();
  int GetRandomEmptyPage();

private:
  Lock *lock;
  BitMap *bitmap;
};

#endif // CHANGED
#endif // PAGEPROVIDER_H
