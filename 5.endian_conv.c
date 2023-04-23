//
// Created by satellite on 2023-04-23.
//

#include "stdio.h"
#include "arpa/inet.h"

int main()
{
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;

    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("Host order port : %#x \n",host_port);
    printf("Network order port : %#x \n",net_port);
    printf("Host order address: %#lx \n",host_addr);
    printf("Network order address: %#lx \n",net_addr);
    return 0;
}

/*
 运行结果：
Host order port : 0x1234
Network order port : 0x3412
Host order address: 0x12345678
Network order address: 0x78563412

这是在小端序的机器上的结果，若为大端序的机器本地字节序将与网络字节序相同
 */