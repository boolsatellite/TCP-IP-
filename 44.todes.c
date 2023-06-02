//
// Created by satellite on 2023-06-02.
//

#include "stdio.h"
#include "fcntl.h"

int main()
{
    FILE * fp;
    int fd = open("data.dat",O_WRONLY|O_CREAT|O_TRUNC);
    if(fd == -1)
    {
        fputs("open error",stdout);
        return -1;
    }
    printf("First file descriptor : %d \n",fd);
    fp = fdopen(fd,"w");
    fputs("TCP/IP SOCKET PROGRAMER \n",fp);  //fp为FILE*
    printf("Second file descriptor : %d \n", fileno(fp));
    fclose(fp);
    return 0;
}