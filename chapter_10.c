//
// Created by satellite on 2023-05-26.
//

// wait  waitpid

/*

#include<sys/wait.h>
pid_t wait(int * statloc);
调用成功返回终止子进程的PID，失败返回 -1
调用此函数时如果已有子进程终止，那么子进程终止时传递的返回值，
将保存到该参数参数所指的内存空间中
但该函数参数指向的单元中还包含其他信息，故需要两个宏来用于分离：
 WIFEXITED:子进程正常终止时返回 true
 WEXITSTATUS:返回子进程的返回值

 if(WIFEXITED(status))
 {
    puts("Normal termination");
    printf("Child pass num %d",WEXITSTATUS(status));
 }
 调用wait函数时，如果没有已终止的子进程，那么程序嫁给你阻塞，知道有子进程终止


 #include<sys/wait.h>
 pid_t waitpid(pid_t pid , int * statloc , int options);
 成功返回终止子进程的pid，失败返回 -1

 * pid：等待终止目标子进程的ID，若传递 -1 则与wait函数相同，可以终止任意子进程
 * statloc：与wait中statloc相同
 * options：传递头文件中 <sys/wait.h>中声明的常量WNOHANG，
            即使没有终止子进程也不会进入阻塞状态，而是返回 0 并推出函数

 */


//信号和signal函数

/*
#include <signal.h>
void (*signal (int signo , void (*func)(int)) ) (int);
 * signo 为信号
 * func 为要调用的函数

 SIGALRM：已到通过alarm函数注册的时间
 SIGINT：输出ctrl + c
 SIGCHLD：子进程终止
 * */


/*
#include <signal.h>

int sigaction(int signo ,const struct sigaction *act , struct sigaction * oldact);

 * signo：信号
 * act：信号处理函数
 * oldact：获取之前注册的信号函数

 sigaction结构体：
 struct sigaction
 {
    void (*sa_handler)(int);   //保存信号处理函数的指针值
    sigset_t sa_mask;          //信号的相关选项与特性，一般设为 0
    int sa_flags;
 }
 */



























