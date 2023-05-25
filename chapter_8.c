//
// Created by satellite on 2023-05-24.
//

//gethostbyname 函数，用于转换字符串格式的域名到IP地址

/*
#include "netdb.h"

struct hostent * gethostbyname(const char * hostname);       hostent是 host entry 的缩写
只要传递域名字符串，就会返回对应的IP地址，地址信息装入hostent结构体中。
成功返回 hostent的地址结构，失败返回 NULL

struct hostent
{
    char *h_name;		 Official name of host.     官方域名
    char **h_aliases;	 Alias list.                除官方外的其他域名
    int h_addrtype;		 Host address type.             地址类型，若为IPV4 则为 AF_INET
    int h_length;		 Length of address.         IP地址的长度，V4为4字节，V6为16字节
    char **h_addr_list;  List of addresses from name server.
    h_addr_list是最重要的成员，此变量以整数形式保存域名对应的IP地址
};

 若只看hostent结构体的定义，其成员h_addr_list是char**类型
     * 但字符串指针实际指向的是（保存的是）in_addr 结构体的地址，而给字符串地址
     * 故需要强制类型转换，使用 inet_ntoa 产生字符串
     *
     * 至于为什么使用char* 而不使用 struct in_addr* 是因为考虑到了通用性，h_addr_list 指向的数组中也可包含IPV6信息

*/


//gethostbyaddr 函数，用于通过IP获取域名

/*
#include "netdb.h"
struct hostent *gethostbyaddr(const char *addr , socklen_t len , int family);
 * addr 含有IP地址信息的in_addr结构体指针。为了同时传递IPV4地址以外的信息，该变量声明为char*
 * len  向第一个参数的地址信息传递字节数，IPV4为4  IPV6为16
 * * family  地址族信息，IPV4为AF_INET  IPV6为AF_INET6



*/












