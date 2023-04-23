cmake_minimum_required(VERSION 3.16)
project(TCP_IP_ C)

set(CMAKE_C_STANDARD 11)

add_executable(TCP_IP_
        2.hello_client.c homework1.5_copy_file.c 3.socket_type_set_protocol.c 4.tcp_client.c 5.endian_conv.c 6.inet_addr.c 7.inet_aton.c 8.inet_ntoa.c)
