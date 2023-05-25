//
// Created by satellite on 2023-05-24.
//

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "netdb.h"

void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc , char * argv[])
{
    int i;
    struct hostent *host;

    if(argc != 2)
    {
        printf("Usage : %s <addr>",argv[0]);
        exit(1);
    }

    host = gethostbyname(argv[1]);

    if(!host)
        error_handling("gethost error");

    printf("official name : %s \n",host->h_name);
    for (int i = 0; host->h_aliases[i]; ++i)
        printf("Aliases %d : %s \n",i+1,host->h_aliases[i]);

    printf("Address type : %s \n",
           (host->h_addrtype==AF_INET) ? "AF_INET" : "AF_INET6");

    for (int i = 0; host->h_addr_list[i]; ++i)
        printf("IP addr %d : %s \n",i+1, inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));

    /*若只看hostent结构体的定义，其成员h_addr_list是char**类型
     * 但字符串指针实际指向的是（保存的是）in_addr 结构体的地址，而给字符串地址
     * 故需要强制类型转换，使用 inet_ntoa 产生字符串
     *
     * 至于为什么使用char* 而不使用 struct in_addr* 是因为考虑到了通用性，h_addr_list 指向的数组中也可包含IPV6信息 */
    return 0;
}

















