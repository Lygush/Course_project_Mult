#include "thread_pool.h"

Thread_pool::Thread_pool() {
    for (int i{}; i < cores - 1; ++i) {
        pool.push_back(std::thread(&Thread_pool::work, this));
    }
}

Thread_pool::~Thread_pool() {
    for (auto &i : pool) {
        i.join();
    }
}

void Thread_pool::work() {
    std::unique_lock<std::mutex> ul(queue.get_mut());
    queue.get_cv().wait(ul, [&](){return !queue.empty();});
    ul.unlock();
    while (!queue.empty()) {
        auto task {queue.pop()};
        task();
    }  
}

void Thread_pool::submit(std::function<void()> func) {
    queue.push(func);
}