//
// Created by satellite on 2023-05-29.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "signal.h"
#include "sys/wait.h"
#include "arpa/inet.h"
#include "sys/socket.h"

#define BUF_SIZE 30

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void read_childproc(int sig);


int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;

    pid_t pid;
    struct sigaction act;
    socklen_t adr_sz;
    int str_len, state;
    char buf[BUF_SIZE];
    if (argc != 2) {
        printf("Usage : %s <port> \n", argv[0]);
        exit(1);
    }
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    state = sigaction(SIGCHLD, &act, 0);  //为信号注册函数

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = PF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket error");

    if (bind(serv_sock, (struct sockaddr *) &serv_adr, sizeof(struct sockaddr)) == -1)
        error_handling("bind error");

    if (listen(serv_sock, 5) == -1)
        error_handling(("listen error"));

    while (1) {
        adr_sz = sizeof clnt_adr;
        clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_adr, &adr_sz);
        if (clnt_sock == -1)
            continue;

        pid = fork();
        if (pid == -1)
            close(clnt_sock);

        if (pid == 0) {
            close(serv_sock);  //关闭子进程中的serv_sock
            while ((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0) {
                write(clnt_sock, buf, str_len);
            }
            close(clnt_sock);   //完成回声后关闭clnt_sock
            puts("clent disconnected...");
            return 0;
        } else
            close(clnt_sock);    //父进程关闭clnt_sock
    }
    close(serv_sock);
    return 0;
}

void read_childproc(int sig)
{
    pid_t pid;
    int status;
    pid = waitpid(-1,&status,0);
    printf("remove proc id : %d \n",pid);
}

/*调用fork函数时复制父进程的所有资源，但套接字并非进程所有
 * 严格意义上套接字属于操作系统————只是进程拥有代表相应套接字的文件描述符
 *
 * 调用fork函数后就存在两个文件描述符指向同一个套接字，
 * 只有2个文件描述符都销毁后，才能终止套接字，
 *
 * 因此调用fork函数后，要将无关的套接字文件描述符关掉*/
