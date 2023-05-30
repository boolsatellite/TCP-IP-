//
// Created by satellite on 2023-05-29.
//

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "arpa/inet.h"
#include "sys/socket.h"

#define BUF_SIZE 30

void error_handling(char *message);
void read_routine(int sock , char *buf);
void write_routine(int sock , char *buf);

int main(int argc , char *argv[])
{
    int sock;
    pid_t pid;
    //char *buf = malloc(sizeof(char ) * BUF_SIZE);
    char buf[BUF_SIZE];
    struct sockaddr_in serv_addr;
    if(argc != 3)
    {
        printf("Usage : %s <IP> <port> \n",argv[0]);
        exit(1);
    }
    sock = socket(PF_INET,SOCK_STREAM,0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
        error_handling("connect error");
    printf("connect... \n");

    pid = fork();
    if(pid == 0)
        write_routine(sock,buf);  //子进程写
    else
        read_routine(sock,buf);   //父进程读

    close(sock);   //父子进程都会执行，故sock会被成功关闭
    return 0;
}


void read_routine(int sock , char * buf)
{
    while(1)
    {
        int str_len = read(sock,buf,BUF_SIZE);
        if(str_len == 0)
            return;
        buf[str_len] = 0;
        printf("Message from server : %s ",buf);
    }
}

void write_routine(int sock , char * buf)
{
    while (1)
    {
        fgets(buf,BUF_SIZE,stdin);
        if(!strcmp(buf,"q\n") || strcmp(buf,"Q\n") == 0)
        {
            shutdown(sock,SHUT_WR);
            /*shutdown会切断进程共享的套接字的所有连接，
             * 不管这个套接字的引用计数是否为零，
             * 那些试图读得进程将会接收到EOF标识，
             * 那些试图写的进程将会检测到SIGPIPE信号，
             * 同时可利用shutdown的第二个参数选择断连的方式。*/
            return;
        }
        write(sock,buf, strlen(buf));
    }
}

void error_handling(char *message)
{
    fputs("message",stderr);
    fputc('\n',stderr);
    exit(1);
}

/*
 shutdown函数第二参数：

SHUT_RD(0)：关闭连接的“读”这个方向，对该socket进行读操作直接返回 EOF，
            从数据角度来看，套接字上接收缓冲区已有的数据将被丢弃，
            如果再有新的数据流到达，会对数据进行 ACK，然后丢弃。
            也就是说，对端还是会接收到 ACK，
            但是在这种情况下根本不知道数据已经被丢弃了。

SHUT_WR(1)：关闭连接的“写”这个方向，在这种情况下，
            连接处于“半关闭”状态，此时，不管socket引用计数的值是多少，
            都会直接关闭连接的写方向。
            套接字上发送缓冲区已有的数据将被立即发送出去，
            并发送一个 FIN 报文给对端。
            应用程序如果对该套接字进行写操作会报错。
            （此时对端仍然可以发送数据，调用shutdown的一端也可以对收到的数据发送ACK）
            （如果有进程共享此socket，那么也会受到影响）

SHUT_RDWR(2)：相当于 SHUT_RD 和 SHUT_WR 操作各一次，关闭套接字的读和写两个方向。
 */

/*
 * close 和 shutdown 的区别

close 会关闭连接，并释放所有连接对应的资源，而 shutdown 并不会释放掉套接字和所有的资源。
确切地说，close用来关闭套接字，将套接字描述符（或句柄）从内存清除，之后再也不能使用该套接字。
应用程序关闭套接字后，与该套接字相关的连接和缓存也失去了意义，TCP协议会自动触发关闭连接的操作。

shutdown() 用来关闭连接，而不是套接字，不管调用多少次 shutdown()，套接字依然存在，
直到调用close将套接字从内存清除。(即调用shutdown后，仍然需要调用close关闭socket)
调用close关闭套接字，或调用shutdown关闭输出流时，都会向对方发送FIN包，
FIN 包表示数据传输完毕，计算机收到 FIN 包就知道不会再有数据传送过来了。


close存在引用计数的概念，并不一定导致该套接字不可用，而shutdown则不会管引用计数，
直接使得该套接字不可用，如果有别的进程企图使用该套接字，将会受到影响。

close 的引用计数导致不一定会发出 FIN 结束报文，而 shutdown 则总是会发出 FIN 结束报文，
这在我们打算关闭连接通知对端的时候，是非常重要的


 https://juejin.cn/post/7041167124785528840
 * */
