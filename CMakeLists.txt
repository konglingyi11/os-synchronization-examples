cmake_minimum_required(VERSION 3.26)
project(os)

set(CMAKE_CXX_STANDARD 11)

# Add executables
add_executable(single_producer-single_consumer 单生产者-单消费者.cpp lib/ThreadManager.h lib/Semaphore.h lib/oslib.h)
add_executable(multiple_producer-multiple_consumer 多生产者-多消费者.cpp)
add_executable(main2 main2.cpp)
