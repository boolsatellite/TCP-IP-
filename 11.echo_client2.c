//
// Created by satellite on 2023-04-25.
//
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "sys/socket.h"
#include "unistd.h"
#include "arpa/inet.h"

//回声问题的解决：
//可以提前确定接收数据的大小，若之前传输了20字节长的字符串，
//则在接收时循环调用read函数读取20字节即可
//代码如下：

#define BUF_SIZE 1024
void error_message(char * message);

int main(int argc , char * argv[])
{
    int sock;
    char message[BUF_SIZE];
    int str_len , recv_len ,recv_cnt;

    struct sockaddr_in serv_adr;

    if(argc != 3)
    {
        printf("Usage : %s <IP> <Port>",argv[0]);
        exit(1);
    }

    sock = socket(PF_INET,SOCK_STREAM,0);
    if(sock == -1)
        error_message("sock() error");

    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = htons(atoi(argv[2]));
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);

    if( connect(sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr)) == -1 )
        error_message("connect() error");
    else
        puts("Connected-----------");

    while(1)
    {
        fputs("Input message(Q to quit) : ",stdout);
        fgets(message,BUF_SIZE,stdin);
        if( !strcmp(message,"q\n") || !strcmp(message,"Q\n"))
            break;

        str_len = write(sock,message, strlen(message));

        recv_len = 0;
        while (recv_len < str_len)   //保证传入传出数据长度相同
        {
            recv_cnt = read(sock,&message[recv_len],BUF_SIZE-1);
            if(recv_len == -1)
                error_message("read() error");
            recv_len += recv_cnt;
        }
        message[recv_len] = 0;
        printf("Message from server : %s \n",message);
    }
    close(sock);
    return 0;
}



void error_message(char * message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    return;
}
