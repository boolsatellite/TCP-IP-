//
// Created by satellite on 2023-06-02.
//

/*
 在sep_sev.c中，读模式FILE* 和 写模式 FILE* 都是基于同一个文件描述符创建的
 因此，针对任意一个FILE指针调用fclose函数时，都会关闭文件描述符，也就终止了套接字
 解决方法：复制一份文件描述符，然后利用各自的文件描述符生成读模式FILE*和写模式FILE*
 这也意味着，只有摧毁所有的文件描述符后才能摧毁套接字，针对写模式FILE*调用fclose时
 只能摧毁与该FILE*相关的文件描述符，无法摧毁套接字。但这任然没有进入半关闭状态，因为
 还存在一个文件描述符，该文件描述符可读可写

 */

//dup  和   dup2

/*
 #include <unistd.h>
 int dup(int fildes);
 int dup2(int fildes , intfildes2);

 * fildes ：需要复制的文件描述符
 * fildes2：明确指定文件描述符的整数值

 */