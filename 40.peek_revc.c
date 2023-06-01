//
// Created by satellite on 2023-06-01.
//

#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"
#include "sys/socket.h"
#include "arpa/inet.h"

#define BUF_SIZE 30

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc , char * argv[])
{
    int acpt_sock , recv_sock;
    struct sockaddr_in acpt_adr , recv_adr;
    int str_len , state;
    socklen_t recv_adr_sz;
    char buf[BUF_SIZE];
    if(argc != 2)
    {
        printf("Usage %s : <port>\n",argv[0]);
        exit(1);
    }
    acpt_sock = socket(PF_INET,SOCK_STREAM,0);
    memset(&acpt_adr,0,sizeof acpt_adr);
    acpt_adr.sin_family = PF_INET;
    acpt_adr.sin_port = htons(atoi(argv[1]));
    acpt_adr.sin_addr.s_addr = htonl(INADDR_ANY);

    if( bind(acpt_sock,(struct sockaddr*)&acpt_adr,sizeof(acpt_adr)) == -1)
        error_handling("bind error");
    listen(acpt_sock,5);

    recv_adr_sz = sizeof recv_adr;
    recv_sock = accept(acpt_sock,(struct sockaddr*)&recv_adr,&recv_adr_sz);

    while (1)
    {
        str_len = recv(recv_sock,buf,sizeof(buf)-1,MSG_PEEK | MSG_DONTWAIT);
        if(str_len > 0)
            break;
    }
    buf[str_len] = 0;
    printf("Bufering %d bytes : %s \n",str_len,buf);

    str_len = recv(recv_sock,buf,sizeof (buf)-1,0);
    buf[str_len] = 0;
    printf("Read again : %s \n",buf);

    close(acpt_sock);
    close(recv_sock);
    return 0;
}

/*输出：
Bufering 3 bytes : 123
Read again : 123*/

/*同时调用 MSG_PEEK 和 MSG_DONTWAIT 选项，以验证输入缓存中存在接收的数据。
 * 设置MSG_PEEK选项并调用recv函数时，即使读取了输入缓冲的数据也不会删除。
 * 因此，该选项通常与 MSG_DONTWAIT合作，保证即使不存待读取数据也不会进入阻塞状态
 * 用于调用以非阻塞方式验证待读数据存在与否的函数*/
