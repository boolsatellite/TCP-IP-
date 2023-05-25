//
// Created by satellite on 2023-04-23.
//


/*
 int inet_aton(const char* string , struct in_addr * addr);
 string：需要转换的IP地址信息的字符串地址
 addr：将保存转换结果的 in_addr 结构
 成功返回 1 失败返回 0
 * */
#include "stdio.h"
#include "stdlib.h"
#include "arpa/inet.h"

void error_message(char *message)
{
    fputs(message,stderr);
    fputc('\n', stderr);
    exit(1);
}


int main()
{
    char *addr = "127.232.124.79";
    struct sockaddr_in addr_inet;

    if(inet_aton(addr,&addr_inet.sin_addr) == 0)
        error_message("Convering error");
    else
        printf("Network order integer addr : %#x \n",addr_inet.sin_addr.s_addr);
    return 0;
}
/*
 * inet_aton函数第二参数类型为 struct in_addr* 类型
 * 与之对应的是 struct sockaddr_in::in_addr
 * */

/*输出：
 Network order integer addr : 0x4f7ce87f
 * */










