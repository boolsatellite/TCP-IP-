//
// Created by satellite on 2023-04-26.
//
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "sys/socket.h"
#include "unistd.h"
#include "arpa/inet.h"

#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4

void error_message(char * message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    return;
}

int main(int argc , char * argv[])
{
    int sock;
    char opmsg[BUF_SIZE];
    int result , opnd_cnt , i;
    struct sockaddr_in serv_adr;
    if(argc != 3)
    {
        printf("Uaage : %s <IP> <Port>",argv[0]);
        exit(1);
    }

    sock = socket(PF_INET,SOCK_STREAM,0);
    if(sock == -1)
        error_message("socket() error");
    memset(&serv_adr,0,sizeof(serv_adr));

    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = htons(atoi(argv[2]));
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);

    if(connect(sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr)) == -1)
        error_message("connect() error");
    else
        puts("Connected___________");

    fputs("Operand count : ",stdout);
    scanf("%d",&opnd_cnt);
    opmsg[0] = (char)opnd_cnt;

    for(i=0;i<opnd_cnt;i++)
    {
        printf("Operator %d : ",i+1);
        scanf("%d",(int*)&opmsg[i * OPSZ  +1]);
    }

    fgetc(stdin);   //除去缓冲区中残留的'\n'
    fputs("Operator : ",stdout);
    scanf("%c",&opmsg[opnd_cnt*OPSZ + 1]);
    write(sock,opmsg,opnd_cnt * OPSZ  +2);
    read(sock,&result,RLT_SIZE);

    printf("Operation result : %d \n",result);
    close(sock);
    return 0;
}






