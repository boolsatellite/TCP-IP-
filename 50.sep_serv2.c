//
// Created by satellite on 2023-06-02.
//

#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "arpa/inet.h"
#include "sys/socket.h"
#include "string.h"

#define BUF_SIZE 1024

int main(int argc , char * argv[])
{
    int serv_sock , clnt_sock;
    FILE * readfp;
    FILE * writefp;

    struct sockaddr_in serv_adr , clnt_adr;
    socklen_t clnt_adr_sz;
    char buf[BUF_SIZE];

    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    memset(&serv_adr,0,sizeof serv_adr);
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr));
    listen(serv_sock,5);
    clnt_adr_sz = sizeof clnt_adr;
    clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);

    readfp = fdopen(clnt_sock,"r");
    writefp = fdopen(dup(clnt_sock),"w"); //针对dup函数返回值生成FILE指针

    fputs("FROM SERVER : HI~ client ? \n",writefp);
    fputs("I love all of the world \n",writefp);
    fputs("You are awesome ! \n",writefp);
    fflush(writefp);

    shutdown(fileno(writefp),SHUT_WR);
    /*针对fileno函数返回文件描述符调用shutdown函数，因此服务器进入半关闭状态
     * 并向客户端发送EOF。
     * 调用shutdown函数时，无论复制出多少文件描述符都会进入半关闭状态，同时传递EOF*/

    fclose(writefp); //关闭复制出来的文件描述符
    fgets(buf,sizeof buf,readfp);
    fputs(buf,stdout);
    fclose(readfp);
    return 0;
}
/*无论复制出多少文件描述符，均应调用shutdown函数发送EOF并进入半关闭状态
 * 第十章中，通过fork函数生成2个文件描述符，并在这种情况下调用shutdown函数
 * 发送了EOF，并进入半关闭状态*/
