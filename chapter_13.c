//
// Created by satellite on 2023-05-31.
//


/*
#include "sys/socket.h"
ssize_t send(int sockfd , const void * buf , size_t nbytes , int flags);
 * sockfd：表示与数据传输对象的连接套接字文件描述符
 * buf：保存带传输数据的缓冲地址值
 * nbytes：待传输数据的字节数
 * flags：传输数据时指定的可选项信息
 *


ssize_t recv(int sockfd , void * buf , size_t nbytes , int flags);
 成功返回接收的字节数，失败返回负数，连接关闭返回0
 * sockfd：表示与数据传输对象的连接套接字文件描述符
 * buf：保存接收数据的缓冲地址值
 * nbytes：可接收数据的最大字节数
 * flags：接收数据时指定的可选项信息

send 和 recv 函数的最后一个参数是收发数据时的可选项，该选项可利用位或(bit OR),
同时传递多个信息如：
 MSG_OOB        用于传输带外数据(Out Of Band)                   send recv
 MSG_PEEK       验证输入缓冲中是否存在接收数据                          recv
 MSG_DONTROUTE  数据传输过程中不参考路由表，在本地网络中寻找目的地   send
 MSG_DONTWAIT   调用I/O函数时不阻塞，用于使用非阻塞IO              send recv
 MSG_WAITALL    防止函数返回，知道接受全部请求的字节数                   recv

 MSG_OOB:发送紧急消息，该可选项用于创建特殊发送方式的通道以发送紧急消息
*/


//readv 和 writev：对数据进行整合传输及发送的函数
/* 通过writev函数可以将分散保存在多个缓冲中的数据一并发送
 * 通过readv 函数可以由多个缓冲分别接收
 * */

/*
 #include <sys/uio.h>
 ssize_t writev(int fileds , const struct iovec * iov , int iovcnt);

 * filedes：表示数据传输对象的套接字文件描述符。但该函数并不只限与套接字，因此可以像read函数
 *          一样向其传递文件或标准标识符
 * iov：iovec结构体数组的地址值，结构体iovc中包含待发送数据的位置和大小信息
 * iovcnt：向第二个参数传递数组长度

 iovec结构体：
 struct iovec{
    void * iov_base;  //缓冲地址
    size_t iov_len;   //缓冲大小
 }


 ssize_t readv(int filedes , const struct iovec * iov , int iovcnt);

 * filedes：传递接收数据的文件或套接字
 * iov：包含数据保存位置和大小信息的iovec结构体数组的地址值
 * iovcnt：第二个参数中数组的长度

 */



















