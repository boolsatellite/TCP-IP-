//
// Created by satellite on 2023-06-02.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"
#define BUF_SIZE 1024

int main(int argc , char * argv[])
{
    int serv_sock , clnt_sock;
    FILE * readfp;
    FILE * writefp;

    struct sockaddr_in serv_adr , clnt_adr;
    socklen_t clnt_adr_sz;
    char buf[BUF_SIZE] = {0};
    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock == -1)
    {
        printf("socket() erro");
        exit(1);
    }
    memset(&serv_adr,0,sizeof serv_adr);
    serv_adr.sin_family = PF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));
    if( bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr)) == -1) {
        printf("bind error\n");
        exit(1);
    }

    listen(serv_sock,5);
    clnt_adr_sz = sizeof clnt_adr;

    clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);
    if(clnt_sock == -1)
        printf("connect error");
    readfp = fdopen(clnt_sock,"r");
    writefp = fdopen(clnt_sock,"w");

    fputs("FROM SERVER : HI~CLIENT \n",writefp);
    fputs("I love all of the world \n",writefp);
    fputs("You are awesome \n",writefp);
    fflush(writefp);
    fclose(writefp);  //针对写模式FILE指针调用fclose，对方主机将收到EOF
    fgets(buf,BUF_SIZE, readfp);
    fputs(buf,stdout);
    fclose(readfp);
    return 0;
}

//服务端并没有收到最后的字符串
//原因：第50行调用 fclose(writefp)函数完全终止了套接字，而不是半关闭。

