//
// Created by satellite on 5/5/2023.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"

#define BUF_SIZE 30
char buf[BUF_SIZE];

void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc , char * argv[])
{
    int sd;
    FILE *fp;
    int read_cnt;
    struct sockaddr_in serv_adr;

/*    if(argc != 3)
    {
        printf("Usage :%s : <IP> <PORT>",argv[0]);
        exit(1);
    }*/

    fp = fopen("receive.dat","wb");

    sd = socket(PF_INET,SOCK_STREAM,0);
    memset(&serv_adr,0,sizeof(serv_adr));

    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_adr.sin_port = htons(9190);

    if(connect(sd,(struct sockaddr*)&serv_adr,sizeof(serv_adr)) == -1)
        error_handling("connect error");
    while ((read_cnt = read(sd,buf,BUF_SIZE)) != 0)
    {
        fwrite((void*)buf,1,read_cnt,fp);
    }
    puts("Recvived file data");
    write(sd,"Thank you",10);
    fclose(fp);
    close(sd);
    return 0;
}
