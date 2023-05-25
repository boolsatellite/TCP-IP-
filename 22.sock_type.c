//
// Created by satellite on 2023-05-25.
//

//getsockopt，示例使用协议层 SOL_SOCKET 名为 SO_TYPE 的可选项查看


#include "stdio.h"
#include "stdlib.h"
#include "sys/socket.h"

void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main()
{
    int tcp_sock , udp_sock;
    int sock_type;
    socklen_t optlen;
    int state;

    optlen = sizeof sock_type;
    tcp_sock = socket(PF_INET,SOCK_STREAM,0);
    udp_sock = socket(PF_INET,SOCK_DGRAM,0);
    printf("SOCK_STREAM:%d \n",SOCK_STREAM);
    printf("SOCK_DGRAM:%d \n",SOCK_DGRAM);

    state = getsockopt(tcp_sock,SOL_SOCKET,SO_TYPE,(void*)&sock_type,&optlen);
    if(state)
        error_handling("getsockopt() error");
    printf("Socket type one : %d \n",sock_type);

    state = getsockopt(udp_sock,SOL_SOCKET,SO_TYPE,(void*)&sock_type,&optlen);
    if(state)
        error_handling("getsockopt() error");
    printf("Socket type two : %d \n",sock_type);
    return 0;
}
/*
 上述为调用getsockopt函数查看套接字的方法，用于验证套接字类型 SO_TYPE 是典型的只读可选项
 “套接字类型只能在创建时决定”

#:/mnt/d/github/TCP-IP-$./bin/22.sock_type
SOCK_STREAM:1
SOCK_DGRAM:2
Socket type one : 1
Socket type two : 2


 * */