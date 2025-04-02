cmake_minimum_required(VERSION 3.10)
project(Kiloscore C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -pthread")

add_executable(kiloscore src/kiloscore.c)
