cmake_minimum_required(VERSION 3.10)
project(SimpleHttpServer)

set(CMAKE_CXX_STANDARD 20)

add_executable(http_server src/main.cpp src/HttpServer.cpp src/Get.cpp
src/Util.cpp)
