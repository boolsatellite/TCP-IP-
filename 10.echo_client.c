//
// Created by satellite on 2023-04-25.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"

#define BUF_SIZE 1024

void err_message(char * message);

int main(int argc , char * argv[])
{
    int sock;
    char message[BUF_SIZE];
    int str_len;
    struct sockaddr_in serv_adr;

    if(argc != 3)
    {
        printf("Usage : %s <ip> <port>",argv[0]);
        exit(1);
    }
    sock = socket(PF_INET,SOCK_STREAM,0);

    memset(&serv_adr,0,sizeof serv_adr);
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = htons(atoi(argv[2]));
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);

    if(connect(sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr)) == -1)
        err_message("connect error");
    else
        printf("connected---------");

    while (1)
    {
        fputs("Input message (Q to quit)",stdout);
        fgets(message,BUF_SIZE,stdin);   //向message中输入数据
        if(!strcmp(message,"q\n") || !strcmp(message,"Q\n"))   //若输入q Q 则退出
            break;

        write(sock,message, strlen(message));
        str_len = read(sock,message,BUF_SIZE-1);
        message[str_len] = 0;
        printf("Message from server : %s",message);
    }
    close(sock);   //close 函数会向套接字发送EOF，意味着文件结束
}

void err_message(char * message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    return;
}


/*
代码中存在的错误：

每次调用write函数都会传毒一个字符串，这种假设在某种程度上是合理的
但是我们在第二章中学到了，"TCP不存在数据边界"上述客户端是基于TCP的
当多次调用write函数传递字符串时，有可能一次性到达服务端，此时客户端也有可能从
服务器收到多个字符串，这不是我们希望的。还可能由于数据太长了需要两个数据包发送
服务端希望调用一次write函数，但如果数据太大，操作系统困难把数据包分成多个发送
客户端可能尚未收到全部数据包就调用共read函数


 * */




















