#ifndef H_USERSEMAPHORES
#define H_USERSEMAPHORES
#include "system.h"
#include "synch.h"
#include "bitmap.h"

class UserSemaphore {
public:

    UserSemaphore(int init_size);
    ~UserSemaphore();
    sem_t      Add(Semaphore *new_sem);
    void       Remove(sem_t slot);
    Semaphore* Get(sem_t slot);

private:

    Lock *lock;
    BitMap *bitmap;
    int size;
    Semaphore * sem_array[];
};

#endif // H_USERSEMAPHORES
