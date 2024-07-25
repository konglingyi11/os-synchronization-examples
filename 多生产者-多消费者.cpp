#include "lib/oslib.h"
#include <iostream>

/*
 * 桌子上有一只盘子，每次只能向其中放入一个水果。
 * 爸爸专向盘子中放苹果(apple)，女儿专等着吃盘子中的苹果。
 * 妈妈专向盘子中放橘子(orange)，儿子专等着吃盘子中的橘子。
 * 只有盘子空时，爸爸或妈妈才可向盘子中放一个水果。
 * 仅当盘子中有自己需要的水果时，儿子或女儿可以从盘子中取出水果。
 */

// 定义水果放置和取出的基本操作
void put_apple() {
    std::cout << "put an apple..." << std::endl;
}

void get_apple() {
    std::cout << "take an apple..." << std::endl;
}

void put_orange() {
    std::cout << "put an orange..." << std::endl;
}

void get_orange() {
    std::cout << "take an orange..." << std::endl;
}

// 定义信号量
Semaphore mutex = 1; // 互斥信号量，确保盘子的互斥使用
Semaphore apple_full = 0; // 表示盘子中有苹果的信号量
Semaphore orange_full = 0; // 表示盘子中有橘子的信号量
Semaphore plate_empty = 1; // 表示盘子为空的信号量，用来控制放水果的操作

// 定义爸爸的行为：放苹果
void father_progress() {
    wait(plate_empty); // 检查盘子是否空，即是否可以放入苹果
    wait(mutex); // 进行互斥操作，确保同一时间只有一个操作对盘子进行访问
    put_apple(); // 放入苹果
    signal(mutex); // 释放互斥锁
    signal(apple_full); // 标记盘子中现有苹果，供女儿消费
}

// 定义女儿的行为：取苹果
void daughter_progress() {
    wait(apple_full); // 确保盘子中有苹果，才可以进行取苹果操作
    wait(mutex); // 进行互斥操作
    get_apple(); // 从盘子中取苹果
    signal(mutex); // 释放互斥锁
    signal(plate_empty); // 标记盘子为空，爸爸或妈妈可以放水果
}

// 定义妈妈的行为：放橘子
void mother_progress() {
    wait(plate_empty); // 检查盘子是否空，即是否可以放入橘子
    wait(mutex); // 进行互斥操作
    put_orange(); // 放入橘子
    signal(mutex); // 释放互斥锁
    signal(orange_full); // 标记盘子中现有橘子，供儿子消费
}

// 定义儿子的行为：取橘子
void son_progress() {
    wait(orange_full); // 确保盘子中有橘子，才可以进行取橘子操作
    wait(mutex); // 进行互斥操作
    get_orange(); // 从盘子中取橘子
    signal(mutex); // 释放互斥锁
    signal(plate_empty); // 标记盘子为空，爸爸或妈妈可以放水果
}

int main() {
    ThreadManager manager;
    manager.add(100, father_progress); // 添加100个爸爸的线程
    manager.add(100, mother_progress); // 添加100个妈妈的线程
    manager.add(100, son_progress); // 添加100个儿子的线程
    manager.add(100, daughter_progress); // 添加100个女儿的线程
    manager.start(); // 启动所有线程
    return 0;
}
