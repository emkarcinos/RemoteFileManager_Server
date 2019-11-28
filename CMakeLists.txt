cmake_minimum_required(VERSION 3.10)
project(RemoteFileManager_Server)

set(CMAKE_C_STANDARD 11)
include_directories(include)

add_executable(RemoteFileManager_Server src/main.c src/tcp_sock.c include/tcp_sock.h)