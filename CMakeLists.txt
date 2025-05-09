cmake_minimum_required(VERSION 3.24)
project(lab07 C)

set(CMAKE_C_STANDARD 11)


include_directories(${CMAKE_SOURCE_DIR}/includes)


add_executable(lab07 src/main.c src/lock.c src/record.c)
