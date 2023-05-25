//
// Created by satellite on 2023-05-25.
//

//SO_REUSEADDR可选项及相关的Time-wait状态很重要    reuse重用

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"

#define TRUE 1
#define FALSE 0

void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc , char *argv[]) {
    int serv_sock, clnt_sock;
    char message[30];
    int option, str_len;
    socklen_t optlen, clnt_adr_sz;
    struct sockaddr_in serv_adr, clnt_adr;
    if (argc != 2) {
        printf("Usage :%s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");

/*

    optlen = sizeof option;
    option = TRUE;
    setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,(void*)&option,optlen);
*/

    memset(&serv_adr, 0, sizeof serv_sock);
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = htons(atoi(argv[1]));
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(serv_sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    clnt_adr_sz = sizeof clnt_adr;
    clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_adr, &clnt_adr_sz);
    if (clnt_sock == -1)
        error_handling("accept() error");
    printf("connected-----------\n");

    while ((str_len = read(clnt_sock, message, sizeof(message))) != 0) {
        write(clnt_sock, message, str_len);
        write(1, message, str_len);
    }

    close(clnt_sock);
    close(serv_sock);
    return 0;
}

/*
 * Time-wait状态
 * 套接字经过四次挥手后并非立即消除，二十经过一段时间的Time-wait状态
 * 只有先断开连接的（先发送FIN消息的）主机才会经过Time-wait状态。
 * 因此，若服务器先断开连接，则无法立即重新允许，套接字处于Time-wait状态，
 * 相应端口正在使用，故bind函数会发生错误。

 * 客户端套接字不会经Time-wait状态？
 * 无论服务端还是客户端，先断开连接的套接字必然会经过Time-wait状态
 * 因为客户端套接字的端口号是任意的，故无需考虑
 * 服务端不同，每次使用的端口号是相同的
 *

 * 套接字的可选项中更改 SO_REUSEADDR 的状态，适当调整该参数，
 * 可将Time-wait状态下的套接字端口号重新分配给新的套接字。
 * SO_REUSEADDR的默认值为 0（假），这意味这默认情况下无法分配Iime-wait下的端口号
 * 只需将该值改为 1 即可在服务端重启时，重新分配Time-wait状态的端口号，
 * 这样就避免了多余的等待时间
 * */























