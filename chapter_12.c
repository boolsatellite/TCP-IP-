//
// Created by satellite on 2023-05-31.
//


/*使用slect函数时，可以将多个文件描述符集中到一起统一监视
    * 是否存在套接字接收数据
    * 无需阻塞传输数据的套接字有哪些
    * 那些套接字发生了异常

slect函数的调用方法和顺序：
 步骤一：设置文件描述符，指定监视范围，设置超时
 步骤二：调用slect函数
 步骤三：查看调用结果


 * */


/*
 select函数：

 #include <sys/select.h>
 #include <sys/time.h>

 int select(int maxfd , fd_set * readset , fd_set * writeset,
            fd_set * exceptset , const struct timeval * timeout);
 成功返回 大于零 的值(文件描述符变化的数量),失败返回 -1
 * maxfd：监视对象文件描述符数量
 * readset：将所有关注“是否存在待读取数据”的文件描述符注册到fd_set型变量，并传递其地址值
 * writeset：将所有关注“是否可传输无阻塞数据”的文件描述符注册到fd_set型变量，并传递其地址值
 * exceptset：将所有关注“是否发生异常”的文件描述符注册到fd_set型变量，并传递其地址值
 * timeout：调用select函数后，为了防止陷入无限阻塞的状态，传递超时（time-out）信息

 文件描述符的监视范围：select函数的第一个参数，只需将最大的文件描述符值 + 1，传入即可

 select函数的超时时间与select函数的最后一个参数有关，
 timeval结构体定义：
 struct timeval{
    long tv_sec;   //second
    long tv_usec;  //microsecond
 }

 本来select函数只有在监视文件描述符发生变化时才返回。如果未发生变化就会进入阻塞状态
 指定超时就是为了防止一直阻塞的发生，这样即使文件描述符未发生变化只要过了指定时间，
 也可以从函数中返回，不过这种情况下，select函数返回 0

 文件描述符的变化是指监视的文件描述符中发生了相应的监视事件。如：
 select函数调用完成后，向其传递的fd_set变量发生了改变，原来为 1 的所有位均变为0
 但发生变化的文件描述符对应的位除外。因此可以认为 值任为 1 的位置上文件描述符发生了改变
 */