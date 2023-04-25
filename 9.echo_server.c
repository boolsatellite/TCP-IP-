//
// Created by satellite on 2023-04-25.
//


#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"

#define BUF_SIZE 1024

void error_message(char * message);

int main(int argc , char* argv[]) {
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];
    int strlen, i;
    socklen_t clnt_adr_sz;

    struct sockaddr_in serv_addr , clnt_addr;

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_message("socket() error");
    if (bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1)
        error_message("bind error");
    if(listen(serv_sock, 5) == -1)
        error_message("listen() error");

    clnt_adr_sz = sizeof(clnt_addr);

    for (i = 0; i < 5; i++)
    {
        clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_addr, &clnt_adr_sz);
        if(clnt_sock == -1)
            error_message("accept error");
        else
            printf("connect client %d \n",i+1);

        while ((strlen = read(clnt_sock,message,BUF_SIZE )) != 0)
            write(clnt_sock,message,strlen);

        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}



void error_message(char * message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    return;
}
