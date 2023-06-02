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
    int sock;
    char buf[BUF_SIZE];
    struct sockaddr_in serv_addr;

    FILE * readfp;
    FILE * writefp;

    sock = socket(PF_INET,SOCK_STREAM,0);
    memset(&serv_addr,0,sizeof serv_addr);
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_family = AF_INET;
    int state = connect(sock,(struct sockaddr*)&serv_addr,sizeof serv_addr);
    if(state == -1)
    {
        printf("connect error \n");
        exit(1);
    }
    readfp = fdopen(sock,"r");
    writefp = fdopen(sock,"w");
    while (1)
    {
        if(fgets(buf,BUF_SIZE,readfp) == NULL)
            break;
        fputs(buf,stdout);
        fflush(stdout);
    }
    fputs("FROM CLIENT : THANK YOU \n",writefp);
    fflush(writefp);
    fclose(writefp);
    fclose(readfp);
    return 0;

}
