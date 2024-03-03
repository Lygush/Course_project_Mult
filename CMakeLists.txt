cmake_minimum_required(VERSION 3.2)
project(Course_project)

set(SOURCES Course_project.cpp safe_queue.cpp thread_pool.cpp)
set(HEADERS safe_queue.h thread_pool.h)

add_executable(Course_project ${SOURCES} ${HEADERS})
