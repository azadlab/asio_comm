cmake_minimum_required(VERSION 2.8.3)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_VERBOSE_MAKEFILE ON)
project(asio_tcp)


find_package(Boost)

#link_directories( /usr/local/lib )

include_directories(${Boost_INCLUDE_DIR})

add_executable(server Server.cpp)
target_link_libraries(server -lboost_system -lboost_thread -lpthread -lboost_serialization)

add_executable(client Client.cpp)
target_link_libraries(client -lboost_system -lboost_thread -lpthread -lboost_serialization)

