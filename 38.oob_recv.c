//
// Created by satellite on 2023-06-01.
//

#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "string.h"
#include "netinet/in.h"
#include "fcntl.h"
#include "signal.h"
#include "sys/socket.h"

#define BUF_SIZE 30

void error_handling(char * message);
void urg_handler(int signo);

int acpt_sock;
int recv_sock;

int main(int argc , char * argv[])
{
    struct sockaddr_in recv_adr , serv_adr;
    int str_len , state;
    char buf[BUF_SIZE];
    socklen_t serv_adr_sz;
    struct sigaction act;
    if(argc != 2)
    {
        printf("usage %s : <PORT>\n",argv[0]);
        exit(1);
    }
    acpt_sock = socket(PF_INET,SOCK_STREAM,0);
    act.sa_handler = urg_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    memset(&recv_adr,0,sizeof(recv_adr));
    recv_adr.sin_family = AF_INET;
    recv_adr.sin_port = htons(atoi(argv[1]));
    recv_adr.sin_addr.s_addr = htonl(INADDR_ANY);

    if( (bind(acpt_sock,(struct sockaddr*)&recv_adr,sizeof(recv_adr))) == -1)
        error_handling("bind() error");
    listen(acpt_sock,5);

    serv_adr_sz = sizeof(serv_adr);
    recv_sock = accept(acpt_sock,(struct sockaddr*)&recv_adr,&serv_adr_sz);

    fcntl(recv_sock,F_SETOWN,getpid());
    /*将文件描述符recv_sock指向的套接字拥有者改为getpid()返回值用作ID的进程
      意味着：文件描述符recv_sock指向的套接字引发的SIGURG信号处理进程变为getpid函数
      返回值用作ID的进程
     */
    state = sigaction(SIGURG,&act,0);

    while( (str_len = recv(recv_sock,buf,sizeof(buf),0)) != 0) //接收普通数据
    {
        if(str_len == -1)
            continue;
        buf[str_len] = 0;
        puts(buf);
    }
    close(recv_sock);
    close(acpt_sock);
    return 0;
}

void urg_handler(int signo)
{
    /*收到MSG_OOB紧急消息时，操作系统会产生SIGURG信号
     * 并调用信号注册函数，*/
    int str_len;
    char buf[BUF_SIZE];
    str_len = recv(recv_sock,buf,sizeof (buf)-1,MSG_OOB);  //接收同样使用紧急消息
    buf[str_len] = 0;
    printf("Urgent message : %s \n",buf);
}


void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

/*输出：
Urgent message : 4
Urgent message : 0
123
56789
 */


/*通过MSG_OOB可选项传输数据时不会加快数据的传输速度，而且通过信号处理函数urg_handler读取
 * 数据时只能读取 1个字节。剩余数据只能通过未设置MSG_OOB可选项的普通输入函数读取。
 * 即真正意义的Out Of Band 需要单独的通信路径告诉传输数据，但TCP不提供，只利用TCP紧急模式
 * 进行传输
 * MSG_OOB的真正意义在于督促数据接收对象尽快处理数据
 * */
















