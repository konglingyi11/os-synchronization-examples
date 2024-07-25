#include "lib/oslib.h"


Data produce_data() {
    // 生产数据
    Data data = 1;
    return data;
}

void consume_data(Data data) {
    // 消费数据 对data 进行一定的处理
}

#define n 10 // 缓冲区总资源数
Semaphore mutex = 1;// 缓冲区互斥信号量
// empty + full = n 缓冲区总资源数
Semaphore empty = n;// 当前缓冲区的空位，即生产者可用的资源数量
Semaphore full = 0;// 当前缓冲区中数据的数量，即消费者可用的资源的数量

void add_data_to_buffer(Data data) {
    std::cout << "data --->>> buffer..." << std::endl;
}

Data get_data_from_buffer() {
    std::cout << "buffer --->>> data..." << std::endl;
    Data data = 1;
    return data;
}

void producer_task() {
    Data data = produce_data();  // 生产数据

    wait(empty);  // 缓冲区是否有空位，即生产者是否有可用资源
    wait(mutex);  // 当前缓冲区是否可用
    add_data_to_buffer(data); // 将数据加入缓冲区
    signal(mutex);  // 解除占用缓冲区
    signal(full);  // 消费者的可用资源数+1
}

void consumer_task() {
    wait(full);  // 缓冲区是否有数据，即消费者是否有可用资源
    wait(mutex);  // 当前缓冲区是否可用
    Data data = get_data_from_buffer();// 从缓冲区取数据
    signal(mutex);  // 解除占用缓冲区
    signal(empty);  // 生产者的可用资源数+1

    consume_data(data);  // 消费数据
}

int main() {
    ThreadManager manager;
    manager.add(100, producer_task); // 加入100个生产者
    manager.add(100, consumer_task); // 加入100个消费者
    manager.start(); // 启动所有线程
    return 0;
}
