#include "thread_pool.h"
#include <iostream>
#include <sstream>
#include <random>

int main() {
    std::mutex m;
    Thread_pool tp{};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(500, 4000);
    std::cout << "Start\n";
    for (int i{}; i < 25; ++i) {
        tp.submit([&, i](){
            int rnd{dist(gen)};

            std::ostringstream ss;
            ss << std::this_thread::get_id();
            std::string id = ss.str();
            while (id.length() != 5) {
                id.insert(0, " ");
            }

            m.lock();
            std::cout << i << " -\tid: " << id <<"\tstart func" << "\n";           
            m.unlock(); 
            std::this_thread::sleep_for(std::chrono::milliseconds(rnd));  
            m.lock();
            std::cout << i << " -\tid: " << id << "\tfunc asleep " << rnd << "ms" << std::endl;
            m.unlock();  
            }); 
    }
}