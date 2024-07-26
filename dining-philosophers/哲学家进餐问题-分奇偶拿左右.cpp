//
// Created by kly on 2024/7/26.
//
#include "../lib/oslib.h"

/**
 * 一张圆桌上坐着 5 名哲学家，每两个哲学家之间的桌上摆一根筷子，桌子的中间是一碗米饭。
 * 哲学家们倾注毕生的精力用于思考和进餐，哲学家在思考时，并不影响他人。
 * 只有当哲学家饥饿时，才试图拿起左、右两根筷子（一根一根地拿起）。
 * 如果筷子己在他人手上，则需等待。饥饿的哲学家只有同时拿起两根筷子才可以开始进餐，当进餐完毕后，放下筷子继续思考。
 */

/**
 * 通过奇数号哲学家先拿左边，偶数号哲学家先拿右边避免死锁
 *
 */
#define NUM_PHILOSOPHERS 5

// 定义信号量
Semaphore chopsticks[NUM_PHILOSOPHERS]; // 表示每根筷子的信号量

// 哲学家的行为
void philosopher_progress(int philosopher_id) {
    while (true) {
        do_something("Philosopher " + std::to_string(philosopher_id) + " is thinking..."); // 哲学家思考

        if (philosopher_id % 2 == 0) { // 偶数号哲学家
            wait(chopsticks[(philosopher_id + 1) % NUM_PHILOSOPHERS]); // 先拿右边的筷子
            wait(chopsticks[philosopher_id]); // 再拿左边的筷子
        } else { // 奇数号哲学家
            wait(chopsticks[philosopher_id]); // 先拿左边的筷子
            wait(chopsticks[(philosopher_id + 1) % NUM_PHILOSOPHERS]); // 再拿右边的筷子
        }

        do_something("Philosopher " + std::to_string(philosopher_id) + " is eating..."); // 哲学家进餐

        signal(chopsticks[philosopher_id]); // 放下左边的筷子
        signal(chopsticks[(philosopher_id + 1) % NUM_PHILOSOPHERS]); // 放下右边的筷子
    }
}

int main() {
    // 初始化筷子的信号量
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        chopsticks[i] = 1;
    }

    ThreadManager manager;
    // 添加哲学家的线程
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        manager.add(1, [i]() { philosopher_progress(i); });
    }
    manager.start(); // 启动所有线程
    return 0;
}
