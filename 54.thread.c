//
// Created by satellite on 2023-06-04.
//


#include <unistd.h>
#include <string.h>
#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"

//#define thread1
//#define thread2
//#define thread3
#define thread4
#ifdef thread1
void * thread_main(void * arg);
int main()
{
    pthread_t t_id;
    int thread_param = 5;

    if(pthread_create(&t_id,NULL,thread_main,(void*)&thread_param) != 0)
    //pthread_create 函数成功返回 0
    {
        puts("pthread_create() error");
        return -1;
    }
    sleep(10);
    puts("end of main");
    return 0;
}

void * thread_main(void * arg)
{
    int i;
    int cnt = *((int*)arg);
    for(i=0;i<cnt;i++)
    {
        sleep(1);
        puts("running thread");
    }
    return NULL;
}
#endif


#ifdef thread2
void* thread_main(void *arg);

int main()
{
    pthread_t tid;
    int thread_param = 5;
    void * thr_ret;

    if(pthread_create(&tid,NULL,thread_main,(void*)&thread_param) != 0)
    {
        puts("thread_create() error");
        return -1;
    }
    if(pthread_join(tid,&thr_ret) != 0)
    {
        puts("pthread_join() error");
        return -1;
    }
    printf("Thread return message : %s \n",(char *)thr_ret);
    free(thr_ret);
    return 0;
}

void * thread_main(void * arg)
{
    int i;
    int cnt = *((int*)arg);
    char * msg = (char *) malloc(sizeof (char) * 50);
    strcpy(msg,"Hello , I'am thread~ \n");

    for(i = 0 ; i < cnt ; i++)
    {
        sleep(1);
        puts("running thread");
    }
    return (void *)msg;
}
#endif


#ifdef thread3
void* thread_main(void * arg);

int sum = 0;

int main()
{
    pthread_t id_t1 , id_t2;
    int range1[] = {1,5};
    int range2[] = {6,10};
    pthread_create(&id_t1,NULL,thread_main,(void*)range1);
    pthread_create(&id_t2,NULL,thread_main,(void*)range2);

    pthread_join(id_t1,NULL);
    pthread_join(id_t2,NULL);
    printf("result :  %d \n",sum);
    return 0;
}

void * thread_main(void * arg)
{
    int start = ((int*)arg)[0];
    int end = ((int*)arg)[1];

    while (start < end)
    {
        sum += start;  //sum属于临界区，但未处理
        start++;
    }
    return NULL;
}
#endif

#ifdef thread4

#define NUM_THREAD 100
void * thread_inc(void * arg);
void * thread_des(void * arg);

long long num = 0;
pthread_mutex_t mutex;

int main()
{
    pthread_t thread_id[NUM_THREAD];
    int i;
    pthread_mutex_init(&mutex,NULL);
    for(i=0;i<NUM_THREAD;i++)
    {
        if(i % 2)
            pthread_create(&thread_id[i],NULL,thread_inc,NULL);
        else
            pthread_create(&thread_id[i],NULL,thread_des,NULL);
    }
    for(i=0;i<NUM_THREAD;i++)
    {
        pthread_join(thread_id[i],NULL);
    }
    printf("result : %lld \n",num);
    pthread_mutex_destroy(&mutex);
    return 0;
}

void * thread_inc(void * arg)
{
    int i;
    pthread_mutex_lock(&mutex);
    for(i=0;i<500000000;i++)
    {
        num += 1;
        pthread_mutex_unlock(&mutex);
        return NULL;
    }
}
void * thread_des(void * arg)
{
    int i;
    for(i=0;i<500000000;i++)
    {
        pthread_mutex_lock(&mutex);
        num -=1;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

#endif
















