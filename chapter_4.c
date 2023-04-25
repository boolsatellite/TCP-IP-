//
// Created by satellite on 2023-04-24.
//

#include "sys/socket.h"

/*
int listen(int sock , int backlog);
sock：希望进入等待连接请求状态的套接字文件描述符，传递的描述符套接字参数成为服务端套接字(监听套接字)
backlog：连接请求等待队列的长度
*/

/*
int accept(int sock , struct sockaddr * addr , socklen_t * addrlen);
sock：服务器套接字文件描述符
addr：保存发起连接请求的客户端地址信息的变量地址，调用函数后向传递来的地址填充客户端信息
addrlen：是存有长度的变量地址，长度为第二参数所指地址信息的长度，函数调用完成后，该变量所指长度呗填入
         客户端填充地址信息的地址长度

函数成功调用时内部将产出用于数据I/O的套接字，并返回其文件描述符。(套接字是自动创建的，并自动与发起连接的客户端建立连接)

 */


/*
int connect(int sock , struct sockaddr * servaddr , socklen_t addrlen);
 sock：客户端套接字文件描述符
 servaddr：保存目标服务器端地址信息的变量地址值
 addrlen：传递第二个结构体参数servaddr的长度

 函数成功返回 0 ，失败返回 -1

 客户端调用connect函数后，发生一下情况才会返回：
 1.服务器接受连接请求
 2.发生断网异常情况而中断连接请求

 需要注意的是：所谓的接收连接，并不意味着调用服务端调用accept函数
 其实是，服务端把连接请求记录到等待队列中，故connect函数返回后不会立即数据交换

 */


/*
 * 客户端何时何地如何分配地址
 * 调用connet函数时，分配地址
 * 操作系统内核分配
 * IP使用本机IP，端口随机
 *
 * 客户端的IP和端口在调用connect函数时自动分配，无需调用bind函数
 * */