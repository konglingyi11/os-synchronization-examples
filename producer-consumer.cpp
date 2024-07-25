#include "lib/oslib.h"


void produce_data() {
    std::cout << "Producing data..." << std::endl;
}

void consume_data() {
    std::cout << "Consuming data..." << std::endl;
}

#define n 10 // 缓冲区总资源数
Semaphore mutex = 1;// 缓冲区互斥信号量
// empty + full = n 缓冲区总资源数
Semaphore empty = n;// 当前缓冲区的空位，即生产者可用的资源数量
Semaphore full = 0;// 当前缓冲区中数据的数量，即消费者可用的资源的数量

void producer_task() {
    wait(empty);  // 缓冲区是否有空位，即生产者是否有可用资源
    wait(mutex);  // 当前缓冲区是否可用
    produce_data();  // 生产数据
    signal(mutex);  // 解除占用缓冲区
    signal(full);  // 消费者的可用资源数+1
}

void consumer_task() {
    wait(full);  // 缓冲区是否有数据，即消费者是否有可用资源
    wait(mutex);  // 当前缓冲区是否可用
    consume_data();  // 消费数据
    signal(mutex);  // 解除占用缓冲区
    signal(empty);  // 生产者的可用资源数+1
}

int main() {
    ThreadManager manager;
    manager.add(100, producer_task);
    manager.add(100, consumer_task);
    manager.start();
    return 0;
}
