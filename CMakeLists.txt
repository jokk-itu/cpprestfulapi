cmake_minimum_required(VERSION 3.9)

set(This CPPTEMPLATE)
project(${This} C CXX)

set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

find_package(cpprestsdk REQUIRED)

add_library(LibsModule
        src/handler.cpp
        src/controllers/controller.cpp
        src/controllers/maker_controller.cpp
        src/db/postgres.cpp
        src/db/mongo.cpp
)

target_link_libraries(LibsModule -lpqxx -lpq cpprestsdk::cpprest -lmongocxx -lbsoncxx)

add_executable(main main.cpp)

target_link_libraries(main LibsModule)
