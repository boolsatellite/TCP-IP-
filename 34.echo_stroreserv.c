//
// Created by satellite on 2023-05-30.
//
#include "stdio.h"
#include "signal.h"
#include "stdlib.h"
#include "wait.h"
#include "unistd.h"
#include "string.h"
#include "arpa/inet.h"
#include "sys/socket.h"
#include "signal.h"

#define BUF_SIZE 100

void error_handling(char * message);
void read_childproc(int sig);



int main(int argc , char * argv[])
{
    int serv_sock , clnt_sock;
    struct sockaddr_in serv_adr , clnt_adr;
    int fds[2];

    pid_t pid;
    struct sigaction act;
    socklen_t adr_sz;
    int str_len , state;
    char buf[BUF_SIZE];
    if(argc != 2)
    {
        printf("Usage %s : <IP> <POORT>",argv[0]);
        exit(1);
    }

    act.sa_handler = read_childproc;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    state = sigaction(SIGCHLD,&act,NULL);  //回收子进程注册函数

    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock == -1)
        error_handling("socket error");
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = htons(atoi(argv[1]));
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr)) == -1)
        error_handling("bind() error");

    if(listen(serv_sock,5) == -1)
        error_handling("listen error");

    pipe(fds);
    pid = fork();
    if(pid == 0)       //用于写文件的子进程
    {
        FILE *fp = fopen("echomsg.txt","w+");
        char msgbuf[BUF_SIZE];
        int i , len;

        for(int i=0;i<10;i++)
        {
            len = read(fds[0],msgbuf,BUF_SIZE);
            fwrite((void*)msgbuf,1,len,fp);
        }
        fclose(fp);
        return 0;
    }

    while (1)
    {
        adr_sz = sizeof (clnt_adr);
        clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_adr,&adr_sz);
        if(clnt_sock == -1)
            continue;
        else
            puts("new client connected...\n");

        pid = fork();
        if(pid == 0)
        {
            close(serv_sock);
            while ((str_len = read(clnt_sock,buf,BUF_SIZE))!= 0)
            {
                write(clnt_sock,buf,str_len);
                write(fds[1],buf,str_len);
            }
            close(clnt_sock);
            puts("client disconnected....\n");
            return 0;
        }
        else
            close(clnt_sock);
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
void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
