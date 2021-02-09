cmake_minimum_required(VERSION 3.9)
project(main)

set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

find_package(cpprestsdk REQUIRED)

ADD_LIBRARY(LibsModule 
    handler.cpp
    controller.cpp
    maker_controller.cpp
    postgres.cpp
    mongo.cpp
)

target_link_libraries(LibsModule -lpqxx -lpq cpprestsdk::cpprest -lmongocxx -lbsoncxx)

add_executable(main main.cpp)

target_link_libraries(main LibsModule)