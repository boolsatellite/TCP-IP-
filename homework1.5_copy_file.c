//
// Created by satellite on 2023-04-20.
//

//#define IO
#define ANSI

#ifdef IO
#include "unistd.h"
#include "stdlib.h"
#include "fcntl.h"
#include "stdio.h"

int main(int argc , char* argv[])
{
    if(argc != 3)
    {
        printf("Usage %s src_file dest_file",argv[0]);
        exit(1);
    }

    int src = open(argv[1],O_RDONLY);
    if(src < 0)
    {
        perror("open src error");
        exit(1);
    }
    int dst = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0777);
    if(dst < 0)
    {
        perror("open dst error");
        exit(1);
    }

    char buf[1024];
    int ret;
    while( (ret = read(src,buf,sizeof(buf))) > 0)
    {
        write(dst,buf,ret);
    }
    close(src);
    close(dst);
}
#endif


#ifdef ANSI

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc,char* argv[])
{
    FILE *src = fopen(argv[1],"r");  //失败返回 nullpre 并设置erno
    FILE *dst = fopen(argv[2],"w");
    if(!src && !dst)
    {
        perror("fopen error");
        exit(1);
    }
    char arr[100] = {0};
    int ret;
    while ((ret = fread(arr,1,1,src) ) != 0)
        //返回读到的块数，由于此时每块大小为1字节，故返回每次读取的字节数，当返回0时，说明读到文件末尾
    {
        fwrite(arr,1,1,dst);
    }
    fclose(src);
    fclose(dst);
    return 0;
}




#endif