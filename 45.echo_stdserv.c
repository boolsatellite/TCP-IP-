//
// Created by satellite on 2023-06-02.
//

#include "stdio.h"
#include "fcntl.h"
#include "stdlib.h"
#include "arpa/inet.h"
#include "sys/socket.h"
#include "unistd.h"

#define BUF_SIZE 1024

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc , char * argv[])
{
    int serv_sock , clnt_sock;
    char message[BUF_SIZE];
    struct sockaddr_in serv_adr , clnt_adr;
    socklen_t clnt_adr_sz;

    serv_sock = socket(AF_INET,SOCK_STREAM,0);
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if( bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    if( listen(serv_sock,5) == -1)
        error_handling("listen error");
    clnt_adr_sz = sizeof clnt_sock;


    int str_len;

    for(int i=0;i<5;i++)
    {
        clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);
        if(clnt_sock == -1)
            error_handling("accept error");
        else
            printf("connect ....\n");
        FILE *readfp = fdopen(clnt_sock,"r");
        FILE *writefp = fdopen(clnt_sock,"w");
        while (!feof(readfp))
        {
            fgets(message,BUF_SIZE,readfp);
            fputs(message,writefp);
            fflush(writefp);
            /*
            int fflush( FILE *stream );

            对于输出流（及最后操作为输出的更新流），
            从 stream 的缓冲区写入未写的数据到关联的输出设备。
            对于输入流（及最后操作为输入的更新流），行为未定义。
            若 stream 是空指针，则冲入所有输出流，包括操作于库包内者，
            或在其他情况下程序无法直接访问者。
            */
        }
        fclose(readfp);
        fclose(writefp);
    }

    close(serv_sock);
    return 0;
}













