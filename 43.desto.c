//
// Created by satellite on 2023-06-02.
//

#include "stdio.h"
#include "fcntl.h"

int main()
{
    FILE * fp;
    int fd = open("data.dat",O_WRONLY | O_CREAT | O_TRUNC);
    if(fd == -1)
    {
        fputs("file open error",stdout);
        return -1;
    }
    fp = fdopen(fd,"w");    //将fd转化为 "w"模式的文件指针
    fputs("Network C programming \n",fp);   //只有FILE指针才可以用于标准IO函数
    fclose(fp);
}

