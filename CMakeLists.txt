cmake_minimum_required(VERSION 3.16)
project(TCP_IP_ C)

set(CMAKE_C_STANDARD 11)

add_executable(TCP_IP_
        30.remove_zombie.c 31.echo_mpserv.c 32.echo_mpclient.c)
