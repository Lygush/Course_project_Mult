#pragma once

#include <queue>
#include <functional>
#include <condition_variable>

class Safe_queue {
    std::queue<std::function<void()>> queue{};
    std::mutex mutex;
    std::condition_variable cv;

public:
    void push(std::function<void()> func);
    std::function<void()> pop();

    bool empty();
    std::condition_variable& get_cv();
    std::mutex& get_mut();
};