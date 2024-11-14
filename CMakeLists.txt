cmake_minimum_required(VERSION 3.10)
project(SimpleHttpServer)

set(CMAKE_CXX_STANDARD 20)

# 包含 src 目录下的所有源文件
file(GLOB SOURCES "src/*.cpp")

add_executable(http_server ${SOURCES})
