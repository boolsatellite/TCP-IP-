//
// Created by satellite on 2023-05-28.
//

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "signal.h"
#include "sys/wait.h"

void read_childproc(int sig)    //回收子进程
{
    int status;
    pid_t id = waitpid(-1,&status,WNOHANG);
    if(WIFEXITED(status))
    {
        printf("Remove proc id : %d \n",id);
        printf("Child send %d \n", WEXITSTATUS(status));
    }
}

int main(int argc , char *argv[])
{
    pid_t pid;
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset((sigset_t *) &act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGCHLD,&act,NULL);
    pid = fork();
    if(pid == 0)
    {
        printf("Hi I'm child process ");
        sleep(10);
        return 12;
    }
    else
    {
        printf("Child pid = %d \n",pid);
        pid = fork();
        if(pid == 0)
        {
            puts("Hi I'm child process");
            sleep(10);
            exit(24);
        }
        else
        {
            int i;
            printf("Child proc id : %d \n",pid);
            for (int i = 0; i < 5; ++i) {
                puts("wait....");
                sleep(5);
            }
        }

    }
    return 0;
}
