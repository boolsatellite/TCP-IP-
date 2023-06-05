//
// Created by satellite on 2023-06-04.
//


//线程函数：
/*
 #include <pthread.h>
 int pthread_create(pthread_t * thread , const pthread_attr_t * attr,
                    void*(* start_routine)(void*) , void * arg);
 成功返回 0 ，失败返回其他值

 int pthread_join(pthread_t thread , void ** status);
 成功返回 0 ，失败返回其他值
    * thread：该参数值ID的线程终止后会从改函数返回
    * status：保存线程main函数返回值的指针变量返回值
 调用该函数的线程将进入等待状态，直到第一个参数为ID的线程终止为止。
 而且可以得到线程的main函数的返回值
 */

/* 大多数标准函数都是线程安全的函数。我们不用自己区分线程安全的函数与线程不安全函数
 * 因为这些平台在定义非线程安全函数的同时，提供了具有相同功能的线程安全函数。
 如：
 struct hostent * gethostbyname(const char * hostname); 是一个线程不安全函数
 同时提供了
 struct hostent_r * gethostbyname(const char * hostname,
                                   struct hostent * result,
                                   char * buffer,
                                   int buflen,
                                   int * h_errnop); 是一个线程安全函数
 线程安全函数名称通常存在后缀 _r 。这显然给程序员带来了沉重的负担，
 只需在头文件前定义 _REENTRANT 宏，即可自动将gethostbyname函数调用改为gethostbyname_r
 无需为了上述宏定义特意添加#define语句，可以在编译时通过添加 -D_REENTRANT选项定义宏
 */


//线程创建与销毁
/*
 #include <pthread.h>
 int pthread_mutex_init(pthread_mutex_t * mutex , const pthread_mutexattr_t * attr);
 int pthread_mutex_destroy(pthread_mutex_t * mutex);
 成功返回 0 失败返回其他值

 创建互斥量需要声明如下 pthread_mutex_t 类型变量：pthread_mutex_t mutex;
 该变量地址将传递给pthread_mutex_init函数，用于保存操作系统创建的互斥量。
 调用pthread_mutex_destroy函数时同样需要该信息，如果不需要特殊的互斥量属性，则向第二参数传NULL
 也可以使用里利用PTHREAD_MUTEX_INITIALIZER宏进行声明如：
 pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 */


//线程加锁与释放
/*
 int pthread_mutex_lock(pthread_mutex_t * mutex);
 int pthread_mutex_unlock(pthread_mutex_t * mutex);
 成功返回 0 失败返回其他值
 */

//信号量的创建与销毁
/*
 #include <semaphore.h>
 int sem_init(sem_t * sem , int pshared , usigned int value);
 int sem_destroy(sem_t * sem);
 成功返回 0 ，失败返回其他值
    * sem：创建信号量时保存信号量的变量地址值，摧毁时需要信号量变量的地址
    * pshared：传递其他值时，创建可由多个进程共享的信号量；传递0时，创建只允许一个进程内部使用的信号量
    * value：指定创建信号量初始值
 */


//信号量的加锁与解锁：
/*
 #include <semaphore.h>
 int sem_post(sem_t * sem);
 int sem_wait(sem_t * sem);
 成功返回 0 失败返回其他值
    * sem：传递保存信号量读取值的变量地址值，传递给 sem_post 时信号量增1，传递给 sem_wait时信号量减1

 */

//线程的销毁
/*
 linux线程并不是在首次调用的线程main函数返回时自动销毁，所有采用两种方式加以明确
 调用 pthread_join    不仅会等待线程终止，还会引导线程销毁，但在线程终止前，调用该函数的线程会进入阻塞状态
 调用 pthread_detach  不会引起线程终止或进入等待状态，可以通过该函数引导销毁线程创建的内存空间
 int pthread_detach(pthread_t thread);
 成功返回 0 ，失败返回其他值
    * thread：终止的同时需要销毁的线程ID

 */





