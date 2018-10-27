cmake_minimum_required(VERSION 3.12)
project(mining C)

set(CMAKE_C_STANDARD 99)

add_executable(mining md5/main.c md5/md5.h)