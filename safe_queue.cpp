#include "safe_queue.h"

void Safe_queue::push(std::function<void()> func) {   
    std::lock_guard<std::mutex> lg(mutex);
    queue.push(func);
    cv.notify_all();
}

std::function<void()> Safe_queue::pop() {
    std::unique_lock<std::mutex> ul(mutex);
    cv.wait(ul, [&](){return !queue.empty();});
    auto tmp{queue.front()};
    queue.pop();
    return tmp;
}

bool Safe_queue::empty() { return queue.empty(); }
std::condition_variable& Safe_queue::get_cv() { return cv; }
std::mutex& Safe_queue::get_mut() { return mutex; }