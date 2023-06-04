//
// Created by satellite on 2023-06-02.
//

/*select 函数的不合理处：
    * 调用select函数后常见的针对所有文件描述符的循环语句
    * 每次调用select函数时都需要向该函数传递监视对象信息

    提高性能的阻碍是每次调用select函数时需要向操作系统传递监视对象信息，应用程序向操作系统
    传递数据将对程序造成很大负担，而且无法通过优化代码解决

    select函数的缺点可以通过如下方式弥补：
    "仅向操作系统传递1次监视对象，监视范围或内容发生变化时只通知发生变化的事项"
    这样就无需每次调用select函数时都向操作系统传递监视对象信息了，linux中支持的是epoll

    epoll函数的优点：
    * 无需编写以监视状态变化为目的的针对所有文件描述符的循环语句
    * 调用对应于select函数的epoll_wait函数时无需每次传递监视对象信息

    epoll服务费需要的3个函数：
    * epoll_create：创建保存epoll文件描述符空间
    * epoll_ctl：向空间注册并注销文件描述符
    * epoll_wait：与select函数类似，等待文件描述符发生变化

    select方式中为了保存监视对象文件描述符，直接声明了 fd_set变量。
    但epoll方式下由操作系统负责保存监视文件描述符，因此需要向操作系统请求创建保存
    文件描述符的空间，此时使用的函数就是epoll_create。
    为了添加和删除监视对象文件描述符，select方式中需要FD_SET，FD_CLR，FD_ISSET函数，
    但在epoll中，通过epoll_ctl请求操作系统完成。
    select方式下调用select函数等待文件描述符的变化，而epoll中调用epoll_wait函数
    select方式通过fd_set变量查看监视对象的状态变化，而epoll方式通过结构体epoll_event
    将发生变化的（发生事件的）文件描述符单独集中到一起
    struct epoll_event{
        __uint32_t events;
        epoll_data_t data;
    }

    typedeg union epoll_data{
        void * ptr;
        int fd;
        __uint32_t u32;
        __uint64_t u64;
    }epoll_data_t;

    声明足够大的epoll_event结构体数组后，传递epoll_wait函数时，发生变化的文件描述符信息
    将被填入数组中。因此无需像select函数那样针对所有文件描述符进行循环

 */

//epoll_create
/*
 #include <sys/epoll.h>
 int epoll_create(int size);
 成功返回 epoll文件描述符，失败返回 -1
    * size ： epoll实例的大小
 调用epoll_create函数创建的文件描述符保存空间称为epoll例程。通过参数size传递的值
 决定epoll例程的大小，但该值只是向操作系统提供的建议值。及size并非决定epoll例程的大小，
 仅供操作系统的参考，linux 2.6.8之后内核完全忽略传入epoll_create函数的size大小，
 因为内核会根据情况调整epoll例程的大小

 epoll_create函数创建的资源与套接字相同，也返回文件描述符，也由操作系统管理。
 该函数返回的文件描述符主要用于区分epoll例程，需要终止时，与躯体文件描述符相同调用close函数
*/

//epoll_ctl
/*
生成epoll例程后，应在其内部注册监视对象文件描述符，此时使用epoll_ctl
 #include <epoll.h>
 int epoll_ctl(int epfd , int op , int fd , struct epoll_event * event);
 成功返回 0 ，失败返回-1
    * epfd：用于注册监视对象的epoll例程的文件描述符
    * op：用于指定监视对象的添加 删除 更改等操作
    * fd：需要注册的监视对象的文件描述符
    * event：监视对象的事件类型

如：
 epoll_ctl(A,EPOLL_CTL_ADD,B,C);
 //epoll例程A中注册文件描述符B，主要目的是监视参数C中的事件
 epoll_ctl(A,EPOLL_CTL_DEL,B,NULL)
 //从epoll例程A中删除文件描述符B，从监视对象中删除时，不需要监视类型故填写NULL

 第二参数 op的可选值及含义：
    * EPOLL_CTL_ADD：将文件描述符注册到epoll例程中
    * EPOLL_CTL_DEL：从epoll例程中删除文件描述符
    * EPOLL_CTL_MOD：更改注册文件描述符的关注事件发生情况

 如前所述，epoll_event结构体用于保存发生事件的文件描述符集合。但也可以在epoll例程中
 注册文件描述符时，用于注册关注的事件。
 如：
    struct epoll_event event;
    ...
    event.events = EPOLLIN;   //发生需要读取数据的事件时
    event.data.fd = sockfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&event);
    ...
    上述代码将sockfd注册到epoll例程epfd中，并在需要读取数据的情况下产生相应事件。

    epoll_event的成员events中可以保存的常量及所指的事件类型：
    * EPOLLIN:需要读取数据的情况
    * EPOLLOUT:输出缓冲为空，可以立即发送数据的情况
    * EPOLLPRI:收到OOB数据的情况
    * EPOLLRDHUP:断开连接或半关闭的情况
    * EPOLLERR:发生错误的情况
    * EPOLLET:以边缘触发的方式得到事件通知
    * EPOLLONESHOT:发生依次事件后，相应文件描述符不再受到事件通知，因此
                    需要向epoll_ctl函数的第二参数传递EPOLL_CTL_MOD，再次设置事件
    可以通过位运算同时传递多个上述参数
*/


//epoll_wait
/*
 #include <sys/epoll.h>
 int epoll_wait(int epfd , struct epoll_event * events , int maxevents , int timeout);
 成功返回发生事件的文件描述符，失败返回 -1
    * epfd：表示事件发生监视范围的epoll例程的文件描述符
    * events：保存发生事件的文件描述符集合的结构体地址值
    * maxevents：第二参数中可以保存的最大事件数
    * timeout：以毫秒为单位的等待时间，传递 -1 ，一直等待直到发生事件

 该函数的调用方式：
 int event_cnt;
 struct epoll_event * ep_events;
 ...
 ep_events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);
 ...
 event_cnt = epoll_wait(epfd,ep_events,EPOLL_SIZE,-1);
 //调用后返回发生事件的文件描述符数，同时在第二个参数所指的缓冲中保存发生事件的文件描述符集合
 //因此无需像select那样插入针对所有文件描述符循环
 */


/*
水平触发(level-trggered)

只要文件描述符关联的读内核缓冲区非空，有数据可以读取，就一直发出可读信号进行通知，
当文件描述符关联的内核写缓冲区不满，有空间可以写入，就一直发出可写信号进行通知


边缘触发(edge-triggered)

当文件描述符关联的读内核缓冲区由空转化为非空的时候，则发出可读信号进行通知，
当文件描述符关联的内核写缓冲区由满转化为不满的时候，则发出可写信号进行通知

所以边缘触发需要一次性的把缓冲区的数据读完为止
 */


/*
 将文件改为非阻塞模式
 int flag = fcntl(fd,F_GETFL,NULL);  //获取当前属性
 fcntl(fd,F_SETFL,flag|O_NONBLOCK);  //在原有属性上添加非阻塞标志


 */



