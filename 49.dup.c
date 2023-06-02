//
// Created by satellite on 2023-06-02.
//

#include "stdio.h"
#include "unistd.h"

int main()
{
    int cfd1 , cfd2;
    char str1[] = "Hi~ \n";
    char str2[] = "It's nice day~ \n";

    cfd1 = dup(1);
    cfd2 = dup2(1,7);

    printf("fd1 = %d , fd2 = %d \n",cfd1,cfd2);
    write(cfd1,str1,sizeof str1);
    write(cfd2,str1,sizeof str2);

    close(cfd1);
    close(cfd2);
    write(1,str1,sizeof(str1));
    close(1);

    write(1,str2,sizeof(str2));
    return 0;
}

/*
#:/mnt/d/github/TCP-IP-$./bin/49.dup
fd1 = 3 , fd2 = 7
Hi~
Hi~
It's nice dHi~
 */