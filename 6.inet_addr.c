//
// Created by satellite on 2023-04-23.
//


#include "stdio.h"
#include "arpa/inet.h"

/*

 in_addr_t inet_addr(const char* string);
 用于将点分十进制IP地址转化位4字节整形数据，
 此函数在转换的同时进行网络字节序转换,得到的即为IP对应的网络字节序
 */

int main(int argc , char * argv[])
{
    char *addr1 = "1.2.3.4";
    char *addr2 = "1.2.3.256";

    unsigned long conv_addr = inet_addr(addr1);
    if(conv_addr == INADDR_NONE)
        printf("Error occure! \n");
    else
        printf("Network order integer addr : %#lx \n",conv_addr);
    conv_addr = inet_addr(addr2);
    if(conv_addr == INADDR_NONE)   //#define	INADDR_NONE		((in_addr_t) 0xffffffff)
        printf("Error occure! \n");
    else
        printf("Network order integer addr : %#lx \n",conv_addr);
    return 0;

}

/*运行结果：
Network order integer addr : 0x4030201
Error occure!
 */

//in_addr_t inet_addr (const char *__cp)
// 函数不仅可以把点分十进制的IP地址转化为32位整型，而且还可以验证IP地址是否有效
// 当IP地址无效时，返回 0xffffffff 对应宏 INADDR_NONE

