//
// Created by satellite on 2023-05-25.
//

/*
 * SO_SNDBUF是输入缓冲大小相关的可选项
 * SO_RCVBUF是输出缓冲大小相关的可选项
 * */
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/socket.h"

void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main()
{
    int sock;
    long long snd_buf , rcv_buf , state;
    socklen_t len;

    sock = socket(PF_INET,SOCK_STREAM,0);
    len = sizeof (snd_buf);
    state = getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&snd_buf,&len);
    if(state)
        error_handling("getsockopt() error");
    printf("Input buffer size : %#llx \n",rcv_buf);
    state = getsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void*)&rcv_buf,&len);
    if(state)
        error_handling("getsockopt() error");
    printf("Output buffer size : %#llx \n",snd_buf);
    return 0;
}


