#include "../lib/oslib.h"
/*
 * 假设一个系统有三个抽烟者进程和一个供应者进程。
 * 每个抽烟者不停地卷烟并抽掉它，但是要卷起并抽掉一支烟，抽烟者需要有三种材料：烟草、纸和胶水。
 * 三个抽烟者中，第一个拥有烟草、第二个拥有纸、第三个拥有胶水。
 * 供应者进程无限地提供三种材料，供应者每次将两种材料放桌子上，拥有剩下那种材料的抽烟者卷一根烟并抽掉它，并给供应者进程一个信号告诉完成了。
 * 供应者就会放另外两种材料再桌上，这个过程一直重复（让三个抽烟者轮流地抽烟）。
 * 本质上这题也属于“生产者-消费者”问题，更详细的说应该是“可生产多种产品的单生产者-多消费者”。
 */

// 定义信号量
Semaphore mutex = 1; // 互斥信号量，确保每次只有一个进程对资源进行操作
Semaphore offer1 = 0; // 表示供应者提供了前两种材料中的一种
Semaphore offer2 = 0; // 表示供应者提供了前两种材料中的另一种
Semaphore offer3 = 0; // 表示供应者提供了前两种材料中的第三种
Semaphore empty = 1; // 表示桌子上没有材料

// 定义供应者的行为：提供两种材料
void producer_progress() {
    int i = 0;
    do {
        wait(empty); // 检查桌子是否空，即是否可以放入材料
        switch (i % 3) {
            case 0:
                wait(mutex); // 进行互斥操作，确保同一时间只有一个操作对资源进行访问
                do_something("put offer1"); // 放入材料1
                signal(mutex); // 释放互斥锁
                signal(offer1); // 标记材料1已放入，供相应的抽烟者消费
                break;
            case 1:
                wait(mutex); // 进行互斥操作
                do_something("put offer2"); // 放入材料2
                signal(mutex); // 释放互斥锁
                signal(offer2); // 标记材料2已放入，供相应的抽烟者消费
                break;
            case 2:
                wait(mutex); // 进行互斥操作
                do_something("put offer3"); // 放入材料3
                signal(mutex); // 释放互斥锁
                signal(offer3); // 标记材料3已放入，供相应的抽烟者消费
                break;
        }
    } while (++i);
}

// 定义抽烟者1的行为：消费材料1并抽烟
void consumer_producer1() {
    wait(offer1); // 确保桌子上有材料1
    wait(mutex); // 进行互斥操作
    do_something("take offer1"); // 取走材料1
    signal(mutex); // 释放互斥锁
    signal(empty); // 标记桌子为空，供应者可以放材料

    do_something("consumer1 smoke"); // 抽烟
}

// 定义抽烟者2的行为：消费材料2并抽烟
void consumer_producer2() {
    wait(offer2); // 确保桌子上有材料2
    wait(mutex); // 进行互斥操作
    do_something("take offer2"); // 取走材料2
    signal(mutex); // 释放互斥锁
    signal(empty); // 标记桌子为空，供应者可以放材料

    do_something("consumer2 smoke"); // 抽烟
}

// 定义抽烟者3的行为：消费材料3并抽烟
void consumer_producer3() {
    wait(offer3); // 确保桌子上有材料3
    wait(mutex); // 进行互斥操作
    do_something("take offer3"); // 取走材料3
    signal(mutex); // 释放互斥锁
    signal(empty); // 标记桌子为空，供应者可以放材料

    do_something("consumer3 smoke"); // 抽烟
}

int main() {
    ThreadManager manager;
    manager.add(1, producer_progress); // 添加1个供应者线程
    manager.add(100, consumer_producer1); // 添加100个抽烟者1的线程
    manager.add(100, consumer_producer2); // 添加100个抽烟者2的线程
    manager.add(100, consumer_producer3); // 添加100个抽烟者3的线程
    manager.start(); // 启动所有线程
    return 0;
}