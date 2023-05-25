//
// Created by satellite on 2023-05-25.
//


//getsockopt   和  setsockopt  用于操作套接字的可选项


/*
#include "sys/socket.h"
int getsockopt(int sock , int level , int optname , void *optval , socklen_t *oplen);
成功返回 0 ，失败返回 -1
 * sock：用于查看选项套接字文件描述符
 * level：要查看的可选项协议层
 * optname：要从查看的可选项名
 * optval：保存查看结果的缓存地址值
 * optlen：向第四参数传递缓冲大小。函数调用后，改变量保存通过第四参数返回的可选信息的字节数


int setsockopt(int sock , int level , int optname , const  void *optval , socklen_t optlen);
成功返回 0 失败返回 -1
 * sock：用于更改可选项的套接字文件描述符
 * level：要更改的可选项协议层
 * optname：要更改的可选名
 * optval：保存要更改信息的缓冲地址值
 * optlen：向第四参数optval传递的可选项信息的字节数



*/



