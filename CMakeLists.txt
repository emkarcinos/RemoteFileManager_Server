cmake_minimum_required(VERSION 3.10)
project(RemoteFileManager_Server)

set(CMAKE_C_STANDARD 11)
include_directories(PUBLIC include)
include_directories(PUBLIC logger/src)

add_executable(RemoteFileManager_Server include/tcp_sock.h
        src/tcp_sock.c
        src/main.c src/connector.c include/connector.h
        logger/src/log.c logger/src/log.h src/applet.c include/applet.h src/io.c include/io.h src/files.c include/files.h include/settings.h include/protocol.h)