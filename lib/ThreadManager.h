//
// Created by kly on 2024/7/25.
//

#ifndef OS_THREADMANAGER_H
#define OS_THREADMANAGER_H

#include <vector>
#include <thread>
#include <algorithm>
#include <random>
#include <functional>

class ThreadManager {
public:
    template<typename Func, typename... Args>
    void add(int count, Func&& func, Args&&... args) {
        for (int i = 0; i < count; ++i) {
            tasks.emplace_back([=]() { func(args...); });
        }
    }

    void start() {
        shuffle_tasks();
        threads.reserve(tasks.size());
        for (const auto& task : tasks) {
            threads.emplace_back(task);
        }

        for (auto &thread: threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

private:
    std::vector<std::function<void()>> tasks;
    std::vector<std::thread> threads;

    void shuffle_tasks() {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(tasks.begin(), tasks.end(), std::default_random_engine(seed));
    }
};

#endif //OS_THREADMANAGER_H
