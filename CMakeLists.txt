cmake_minimum_required(VERSION 3.16)
project(TCP_IP_ C)

set(CMAKE_C_STANDARD 11 )
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -pthread")

add_compile_options()

add_executable(TCP_IP_
        57.chat_clnt.c 58.webserv.c)
