# include "pageprovider.h"
# include "synch.h"
# include "system.h"
# include <stdlib.h>
# include <time.h>

#ifdef CHANGED

// =============================================================================
PageProvider::PageProvider() {
    lock   = new Lock("Page Provider Lock");
    bitmap = new BitMap(NumPhysPages);
}

// =============================================================================
PageProvider::~PageProvider() {
    delete bitmap;
    delete lock;
}

// =============================================================================
int
PageProvider::GetEmptyPage() {
    int free = -1;

    lock->Acquire();
    free = bitmap->Find();
    memset(&(machine->mainMemory[free * PageSize]), 0, PageSize);
    lock->Release();
    return free;
}

// =============================================================================
int
PageProvider::GetRandomEmptyPage() {
  int clear = 0, random_rank;

  lock->Acquire();

  clear = bitmap->NumClear();

  srand(time(NULL));
  random_rank = rand() % clear;

  int found = -1;

  for (int i = 0; i < NumPhysPages; i++) {
      if (!bitmap->Test(i)) {
          found++;
          if (found == random_rank) {
              bitmap->Mark(i);
              lock->Release();
              return i;
          }
      }
  }
  lock->Release();
  return -1;
}

void
PageProvider::ReleasePage(int busy) {
  lock->Acquire();
  bitmap->Clear(busy);
  lock->Release();
}

int
PageProvider::NumAvailPage() {
  int clear = 0;

  lock->Acquire();
  clear = bitmap->NumClear();
  lock->Release();
  return clear;
}

#endif // CHANGED
