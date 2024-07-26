#include "../lib/oslib.h"

/**
 * 有读者和写者俩组并发进程，共享一个文件。
 * 当两个或两个以上的读进程同时访问共享数据时不会产生副作用，但若某个写进程和其他进程（读进程或写进程）同时访问共享数据时则可能导致数据不一致的错误。
 * 因此要求：
 * 1.允许多个读者可以同时对文件执行读操作；
 * 2.只允许一个写者往文件中写信息；
 * 3.任一写者在完成写操作之前不允许其他读者或写者工作；
 * 4.写者执行写操作前，应让己有的读者和写者全部退出。
*/
int reader_count = 0;      // 当前读取文件的读者数量
Semaphore read_mutex = 1;  // 控制对 reader_count 的访问
Semaphore rw = 1;          // 确保一次只有一个写者可以访问文件

/**
 * 通过w信号量，实现了一种先到先得（FIFO）的访问策略，无论是读者还是写者，
 * 都必须先获取w信号量。这有助于避免长时间的等待和可能的饥饿问题。
 */
Semaphore w = 1;           // 用于实现“读写公平”

// 定义写者的行为
void writer_progress() {
    while (true) {
        wait(w);          // 请求写操作的公平访问
        wait(rw);         // 请求对写操作的独占访问
        do_something("write file!");  // 执行写操作
        signal(rw);       // 释放对写操作的独占访问
        signal(w);        // 释放写操作的公平访问
    }
}

// 定义读者的行为
void reader_progress() {
    while (true) {
        wait(w);          // 请求读操作的公平访问
        wait(read_mutex); // 获取读者计数的互斥访问
        reader_count++;   // 增加读者计数
        if (reader_count == 1) { // 如果是第一个读者，则尝试获取写者锁，防止写操作
            wait(rw);
        }
        signal(read_mutex); // 释放对读者计数的互斥访问
        signal(w);          // 释放读操作的公平访问

        do_something("read file!"); // 执行读操作

        wait(read_mutex); // 再次获取互斥访问以减少读者计数
        reader_count--;   // 减少读者计数
        if (reader_count == 0) { // 如果是最后一个读者，则释放写者锁
            signal(rw);
        }
        signal(read_mutex); // 释放对读者计数的互斥访问
    }
}

int main() {
    ThreadManager manager;
    manager.add(100, writer_progress); // 添加100个写者线程
    manager.add(100, reader_progress); // 添加100个读者线程
    manager.start(); // 启动所有线程
    return 0;
}
