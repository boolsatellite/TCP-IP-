//
// Created by satellite on 2023-04-21.
//

//套接字类型与协议设置

#include "sys/socket.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "stdio.h"
#include "sys/socket.h"

int main()
{
    int tcp_socket = socket(PF_INET, SOCK_STREAM, 0); //IPV4中面向连接的套接字
    // PF_INET指IPV4网络协议族，SOCK_STREAM是面向连接的数据传送方式，满足这两个条件的只有IPPROTO_TCP

    int udp_socker = socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);//IPV4协议族中面向消息的套接字
    //SOCK_DGRAM指的是面向消息的数据传送方式，满足前两个参数的协议只有IPPROTO_UDP

    struct sockaddr_in addr;


}