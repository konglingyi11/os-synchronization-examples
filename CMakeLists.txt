cmake_minimum_required(VERSION 3.26)
project(os)

set(CMAKE_CXX_STANDARD 11)

# Add executables
add_executable(single_producer-single_consumer producer-consumer/单生产者-单消费者.cpp lib/ThreadManager.h lib/Semaphore.h lib/oslib.h)
add_executable(multiple_producer-multiple_consumer producer-consumer/多生产者-多消费者.cpp)
add_executable(single_producer-multiple_consumer producer-consumer/生产多种产品的单生产者-多消费者.cpp)
add_executable(sleeping-barber producer-consumer/多生产者-单消费者.cpp)
add_executable(reader-writer reader-writer/读者-写者.cpp)
add_executable(dining-philosophers1 dining-philosophers/哲学家进餐问题-限制进餐人数.cpp)
add_executable(dining-philosophers2 dining-philosophers/哲学家进餐问题-分奇偶拿左右.cpp)
add_executable(dining-philosophers3 dining-philosophers/哲学家进餐问题-一个人拿完筷子其他人才可以拿筷子.cpp)
