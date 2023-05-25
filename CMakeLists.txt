cmake_minimum_required(VERSION 3.16)
project(TCP_IP_ C)

set(CMAKE_C_STANDARD 11)

add_executable(TCP_IP_
          21.gethostbyaddr.c chapter_9.c 22.sock_type.c 23.get_buf.c 24.set_buf.c 25.reuseadr_eserver.c)
