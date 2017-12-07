#ifdef CHANGED
# include "usersemaphores.h"

/* ========================================================================= */
UserSemaphore::UserSemaphore(int init_size) {
    size = init_size;
    // sem_array  = new Semaphore[init_size];
    bitmap     = new BitMap(size);
    lock       = new Lock("User Semaphore Lock");
}

/* ========================================================================= */
UserSemaphore::~UserSemaphore() {
    for (int i = 0; i < size; i++)
      delete sem_array[i];
    delete bitmap;
    delete lock;
}

/* ========================================================================= */
sem_t
UserSemaphore::Add(Semaphore * new_sem) {
    lock->Acquire();
    int new_slot = bitmap->Find();

    if (new_slot == -1) {
        ASSERT(false);
    }

    sem_array[new_slot] = new_sem;
    lock->Release();
    return (sem_t)new_slot;
}

/* ========================================================================= */
Semaphore *
UserSemaphore::Get(sem_t slot) {
    lock->Acquire();
    ASSERT(bitmap->Test(slot));
    Semaphore * requested = sem_array[slot];
    lock->Release();
    return requested;
}

/* ========================================================================= */
void
UserSemaphore::Remove(sem_t slot) {
    lock->Acquire();
    ASSERT(bitmap->Test(slot));
    delete sem_array[slot];
    bitmap->Clear(slot);
    lock->Release();
}

/* ========================================================================= */

#endif // CHANGED
