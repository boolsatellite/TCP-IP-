//
// Created by satellite on 2023-04-20.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"

void error_handling(char *message);

int main(int argc,char *argv[])
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[] = "Hello World!";

    if(argc != 2)
    {
        printf("Usage : %s <IP> <port>\n",argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET,SOCK_STREAM,0);   //调用socket创建创建套接字
    if(serv_sock == -1)
        error_handling("sock() error");

    memset(&serv_addr,0,sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1) //bind函数绑定ip地址和端口号
        error_handling("bind() error");
    if(listen(serv_sock,5) == -1)   //将套接字转为课接收连接状态
        error_handling("listen() error");

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);  //受理连接请求若没有连接请求则该函数不会返回，直到有连接请求为止
    if(clnt_sock == -1)
        error_handling("accept() error");

    write(clnt_sock,message,sizeof(message));
    close(clnt_sock);
    close(serv_sock);
}

void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}






















