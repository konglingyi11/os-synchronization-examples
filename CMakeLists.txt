cmake_minimum_required(VERSION 3.26)
project(os)

set(CMAKE_CXX_STANDARD 11)

# Add executables
add_executable(producer_consumer 单生产者-单消费者.cpp lib/ThreadManager.h lib/Semaphore.h lib/oslib.h)
add_executable(main1 main1.cpp)
add_executable(main2 main2.cpp)
