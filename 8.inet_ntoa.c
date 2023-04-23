//
// Created by satellite on 2023-04-23.
//

/*
 * inet_ntoa 与 inet_aton 正好相反，
 * 此函数可以将网络字节序整型IP地址转化为点分十进制的ip地址字符串
 * */

/*
char* inet_ntoa(struct in_addr adr)
 成功转换返回字符串地址，失败返回 -1
 * */



/* 该函数将参数传入的整型IP地址转换为字符串格式并返回，但调用时要小心
 * 返回值类型为char* 返回字符串地址意味着字符串已经保存到了内存空间
 * 但该函数未向程序员要求分配空间，而是在内部申请空间保存字符串。也就是说
 * 调用完inet_ntoa函数后应该理解将字符串信息复制到其他内存中。
 * 因为若再次调用inet_ntoa函数，则有可能覆盖之前的字符串
 * 总之，再次调用inet_ntoa函数前返回的字符串地址值是有效的，若要长期保存，
 * 应将字符串复制到其他内存空间
 * */


#include "arpa/inet.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"



int main()
{
    struct sockaddr_in addr1,addr2;
    char* str_ptr;
    char str_arr[20];

    addr1.sin_addr.s_addr = htonl(0x1020304);
    addr2.sin_addr.s_addr = htonl(0x1010101);

    str_ptr = inet_ntoa(addr1.sin_addr);
    strcpy(str_arr,str_ptr);
    printf("Dotted-Decimal notation1 : %s \n",str_ptr);

    inet_ntoa(addr2.sin_addr);
    printf("Dotted-Decimal notation2 : %s \n",str_ptr);
    printf("Dotted-Decimal notation3 : %s \n",str_arr);

}
/*
输出：
Dotted-Decimal notation1 : 1.2.3.4
Dotted-Decimal notation2 : 1.1.1.1
Dotted-Decimal notation3 : 1.2.3.4
*/



//针对服务器的 网络地址的初始化：
void inet_addr_init1()
{
    struct sockaddr_in addr;
    char * serv_ip = "211.217.168.13";
    char * serv_port = "9190";
    memset(&addr,0,sizeof(addr));  //为了将成员sin_zero初始化为0
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(serv_ip);
    addr.sin_port = htons(atoi(serv_port));
}


//每次常见服务器端套接字都要输入IP有些繁琐，可以驶入如下初始化：
void inet_addr_init2()
{
    struct sockaddr_in addr;
    char * serv_port = "9190";

    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(serv_port));
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //#define	INADDR_ANY		((in_addr_t) 0x00000000)

    /*与之前的最大区别，利用常数：INADDR_ANY 自动分配服务器IP地址
     * 若同一计算机已分配多个IP地址，则只要端口号相同，就可以从不同
     * IP地址接收数据，故服务器优先采用这种方式
     * */
}


//服务器常见套接字初始化过程：

/*bind函数
 * int bind(int sockfd , struct sockaddr * myaddr , socklen_t addrlen);
 * sockfd：要分配地址信息(IP和端口号)的套接字
 * myaddr：存有相关地址信息的结构体
 * addrlen：第二参数结构体的长度，单位字节
 *
 * 成功返回 0 失败返回 -1
 * 若调用成功则将第二参数的地址星系绑定到第一参数所指定的套接字上
 * */
void bind_socker()
{
    int serv_sock;
    char * serv_port = "9190";

    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(serv_port));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    serv_sock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof (serv_addr));

}












