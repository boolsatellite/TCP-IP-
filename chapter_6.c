//
// Created by satellite on 5/4/2023.
//

/*
 * UDP中的IO函数:

ssize_t sendto(int sock , void *buff , size_t nbytes , int flags,
               struct sockaddr *to , socklen_t addrlen);
参数：
 sock:用于传输数据的UDP套接字文件描述符
 buff:保存待传输数据的缓冲地址值
 nbytes:待传输的数据长度，以字节为单位
 flags:可选参数，若没有则传递0
 to:存有目标地址信息的sockaddr结构体变量的地址值
 addrlen:传递给参数to的地址值结构体变量长度

返回值：
 成功返回传输的字节数，失败返回 -1
*/

/*
ssize_t recvfrom(int sock , void *buff , size_t nbytes , int flags,
                 struct sockaddr *from , socklen_t *addrlen);
参数：
 sock:用于接收数据的UDP套接字的文件描述符
 buff:保存接收书的缓冲区地址值
 nbytes:可接收的最大字节数，故无法超过参数buff所指的缓冲区大小
 from:传出参数，存有发送端地址信息的sockaddr结构体变量的地址值
 addrlen:保存参数from结构体变量长度的地址值

返回值：
 成功返回传输的字节数，失败返回 -1

*/














