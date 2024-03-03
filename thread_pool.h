#pragma once

#include <iostream>

#include <vector>
#include <thread>
#include "safe_queue.h"
#include <functional>


class Thread_pool {
    const int cores = std::thread::hardware_concurrency();
    std::vector<std::thread> pool{};
    Safe_queue queue{};

public:
     Thread_pool();
     ~Thread_pool();

     void work();
     void submit(std::function<void()> func);
};

