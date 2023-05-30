//
// Created by satellite on 2023-05-27.
//

#include "stdio.h"
#include "unistd.h"
#include "signal.h"

void timeout(int sig)
{
    if(sig == SIGALRM)
        puts("Time out");
    alarm(2);
}

void keycontrol(int sig)
{
    if(sig == SIGINT)
        puts("CREL + C");
}

int main1()
{
    int i;
    signal(SIGINT,keycontrol);
    signal(SIGALRM,timeout);

    alarm(2);

    for (int i = 0; i < 3; ++i) {
        puts("wait.....");
        sleep(100);
    }
    return 0;
}


int main()
{
    int i;
    struct sigaction act;
    act.sa_restorer = timeout;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM,&act,0);

    alarm(2);
    for(int i=0;i<3;i++)
    {
        puts("wait...");
        sleep(100);
    }
    return 0;
}












