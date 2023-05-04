//
// Created by satellite on 2023-04-25.
//

//本章将讲解详细的TCP必要理论，还将给出第4章客户端问题的解决方案

/*第四章中客户端的问题所在：
     while (1)
    {
        fputs("Input message (Q to quit)",stdout);
        fgets(message,BUF_SIZE,stdin);   //向message中输入数据
        if(!strcmp(message,"q\n") || !strcmp(message,"Q\n"))   //若输入q Q 则退出
            break;

        write(sock,message, strlen(message));
        str_len = read(sock,message,BUF_SIZE-1);
        message[str_len] = 0;
        printf("Message from server : %s",message);
    }
    客户端传输的是字符串，而且是通过write函数一次性发送的，之后希望调用一次read函数接受到自己发送的字符串
    既然回声客户端会收到所有的字符串数据，那么只需等待一段时间即可收到所有的字符串数据
 *
 * */


//TCP理论：
/*IO缓冲的特性：
 * IO缓冲在每个TCP套接字中单独存在
 * IO缓冲在创建套接字时自动生产
 * 即使关闭套接字也会继续传递输出缓冲区中遗留的数据
 * 关闭套接字将丢失输入缓冲区中的数据*/





