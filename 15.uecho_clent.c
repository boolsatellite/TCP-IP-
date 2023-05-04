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
    char message[BUFSIZ];
    int str_len;
    socklen_t adr_sz;

    struct sockaddr_in serv_adr , from_adr;
    if(argc != 3)
    {
        printf("--------\n");
        exit(1);
    }
    sock = socket(PF_INET,SOCK_DGRAM,0);
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));
    serv_adr.sin_family = AF_INET;

    while (1)
    {
        fputs("Insert messaage q to quit\n",stdout);
        fgets(message,sizeof (message),stdin);
        if(!strcmp(message,"q\n"))
            break;
        sendto(sock,message, strlen(message),0,
               (struct sockaddr*)&serv_adr,sizeof (serv_adr));

        adr_sz = sizeof(from_adr);

        str_len = recvfrom(sock,message,BUFSIZ,0,
                           (struct sockaddr*)&serv_adr,&adr_sz);
        message[str_len] = 0;
        printf("Message form server : %s",message);
    }
    close(sock);
    return 0;
}







