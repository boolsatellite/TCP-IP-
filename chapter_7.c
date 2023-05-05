//
// Created by satellite on 5/5/2023.
//

//shutdown函数 用于半关闭优雅的关闭socket连接
/*
 int shutdown(int sock , int howto);
 参数：
 sock:需要断开的套接字文件描述符
 howto:传递断开方式信息，可选：
    SHUT_RD:断开输入流,套接字无法接收数据，即使输入缓冲区收到数据也会被抹去，而且无法调用相关函数
    SHUT_WR:断开输出流,无法传输数据，但如果输出缓冲区中还有未传输的数据则将传递至目标主机
    SHUT_RDWR:同时断开IO流
 返回值：
 成功返回0，失败返回-1
 */















