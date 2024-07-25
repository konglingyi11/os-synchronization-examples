//
// Created by kly on 2024/7/25.
//

#ifndef OS_SEMAPHORE_H
#define OS_SEMAPHORE_H


#include <semaphore.h>

class Semaphore {
public:
    Semaphore() = default;

    Semaphore(int value) {
        sem_init(&sem, 0, value);
    }

    Semaphore &operator=(int value) {
        sem_destroy(&sem); // Destroy any existing semaphore
        sem_init(&sem, 0, value);
        return *this;
    }

    void wait() {
        sem_wait(&sem);
    }

    void signal() {
        sem_post(&sem);
    }

    ~Semaphore() {
        sem_destroy(&sem);
    }

private:
    sem_t sem;
};

#define wait(x) (x).wait()
#define signal(x) (x).signal()
#define P(x) (x).wait()
#define V(x) (x).signal()
#endif //OS_SEMAPHORE_H

