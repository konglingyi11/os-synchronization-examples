//
// Created by kly on 2024/7/26.
//
#include <unistd.h>
#include "../lib/oslib.h"

/**
 * 一个理发师在他的理发店里工作，店内只有一个理发椅和一些等候椅。
 * 如果没有客户，理发师会坐在理发椅上睡觉。当客户到来时，
 * 如果理发师正在睡觉，客户会唤醒他，然后坐在理发椅上接受服务；
 * 如果理发师正在为其他客户服务，并且有空余的等候椅，新到的客户会在等候椅上等待；
 * 如果没有空余的等候椅，客户会离开。
 */
//
// Created by kly on 2024/7/26.
//
#define NUM_WAITING_CHAIRS 5 // 等候椅数量

Semaphore barber = 0; // 理发师目前是否空闲，顾客所需的资源
Semaphore customer = 0; // 等待的顾客数，理发师所需的资源
Semaphore mutex = 1; // 控制对waiting互斥访问

int waiting = 0; // 等待的顾客数量

// 理发师的行为
void barber_progress() {
    while (true) {
        wait(customer); // 等待顾客到来的信号
        wait(mutex); // 获取waiting互斥访问权
        waiting--; // 减少等待顾客数量
        signal(mutex); // 释放waiting互斥访问权
        signal(barber); // 发送理发师现在可用的信号

        do_something("cutting hair");
    }
}

// 顾客的行为
void customer_progress() {
    wait(mutex); // 请求waiting互斥访问权
    if (waiting < NUM_WAITING_CHAIRS) { // 检查是否有空余的等候椅
        waiting++; // 增加等待顾客数量
        signal(mutex); // 释放waiting互斥访问权

        signal(customer); // 来一个顾客，理发师所需资源+1
        wait(barber); // 等待理发师，请求顾客所需的资源

        do_something("getting a haircut.");
    } else {
        signal(mutex); // 释放waiting互斥访问权
        do_something("customer left");
    }
}

int main() {


    return 0;
}
