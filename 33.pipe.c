//
// Created by satellite on 2023-05-30.
//

#include "unistd.h"
#include "stdio.h"

#define BUF_SIZE 30

//#define pipe1
//#define pipe2
#define pipe3

#ifdef pipe1
int main()
{
    int fds[2];
    char str[] = "who are you";
    char buf[BUF_SIZE];
    pid_t pid;

    pipe(fds);
    pid = fork();
    if(pid == 0)
    {
        write(fds[1],str,sizeof str);
    }
    else
    {
        read(fds[0],buf,BUF_SIZE);
        puts(buf);
    }
    return 0;
}
#endif


#ifdef pipe2
//不建议使用一个管道完成双向通信

int main()
{
    int fd[2];
    char str1[] = "Who are you";
    char str2[] = "Thank you for your message";
    char buf[BUF_SIZE];
    pid_t pid;

    pipe(fd);
    pid = fork();
    if(pid == 0)
    {
        write(fd[1],str1,sizeof(str1));
        //sleep(2);
        read(fd[0],buf,BUF_SIZE);
        printf("Child proc output : %s \n",buf);
    }
    else
    {
        read(fd[0],buf,BUF_SIZE);
        printf("Parent proc output : %s \n",buf);
        write(fd[1],str2,sizeof (str2));
    }
    return 0;
}

#endif


#ifdef pipe3
int main()
{
    int fd1[2] , fd2[2];
    char str1[] = "Who are you";
    char str2[] = "Thank you for your message";
    char buf[BUF_SIZE];
    pid_t pid;
    pipe(fd1);
    pipe(fd2);

    pid = fork();
    if(pid == 0)
    {
        write(fd1[1],str1,sizeof(str1));
        read(fd2[0],buf,BUF_SIZE);
        printf("Child proc output : %s \n",buf);
    }
    else
    {
        read(fd1[0],buf,BUF_SIZE);
        write(fd2[1],str2,sizeof(str2));
        printf("Parent proc output : %s \n",buf);
    }
}


#endif



















