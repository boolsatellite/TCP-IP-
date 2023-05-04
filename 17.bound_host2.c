//
// Created by satellite on 5/4/2023.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"

#define BUF_SIZE 30
void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc , char * argv[])
{
    int sock;
    char msg1[] = "Hi";
    char msg2[] = "I'm another UDP host";
    char msg3[] = "Mice to meet you";

    struct sockaddr_in your_adr;
    socklen_t your_adr_sz;

    if(argc != 3)
    {
        printf("usage : %s <ip> <port>",argv[0]);
        exit(1);
    }

    sock = socket(PF_INET,SOCK_DGRAM,0);
    your_adr.sin_addr.s_addr = inet_addr(argv[1]);
    your_adr.sin_port = htons(atoi(argv[2]));
    your_adr.sin_family = AF_INET;

    sendto(sock,msg1,sizeof(msg1),0,
           (struct sockaddr*)&your_adr,sizeof(your_adr));

    sendto(sock,msg1,sizeof(msg2),0,
           (struct sockaddr*)&your_adr,sizeof(your_adr));

    sendto(sock,msg1,sizeof(msg3),0,
           (struct sockaddr*)&your_adr,sizeof(your_adr));

    close(sock);
    return 0;
}



























