//
// Created by satellite on 2023-05-26.
//

#include "stdio.h"
#include "unistd.h"


int main()
{
    pid_t pid = fork();

    if(pid == 0)
    {
        puts("i'm chile process");
    }
    else
    {
        printf("Child Process id : %d \n",pid);
        sleep(30);
    }
    if(pid == 0)
        puts("End child process");
    else
        puts("End parent process");
    return 0;
}

/*
 * 向exit函数传递的参数和main函数的return语句返回的值都会传递给操作系统
 * 而操作系统不会销毁子进程，知道把这些值传递给产生给子进程的父进程。
 * 处于这种状态的进程就是僵尸进程
 *
 * 僵尸进程的销毁应该向创建子进程的父进程传递返回值
 *
 * 但是操作系统不会主动将这些值传递给父进程。
 * 只有在父进程主动发起请求时，操作系统才会传递该值，即wait函数
 * 若父进程未主动要求获取子进程的结束状态，操作系统将一直保留，并让子进程一直处于僵尸状态
 *
 * */