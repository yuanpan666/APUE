#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

static void cleanup_func(void *p)
{
    puts(p);
}


static void *func(void *p)
{
    puts("thread is workding");
    //return NULL;

    pthread_cleanup_push(cleanup_func,"cleanup:1");
    pthread_cleanup_push(cleanup_func,"cleanup:2");
    pthread_cleanup_push(cleanup_func,"cleanup:3");

    puts("push over");

    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid;
  
    int err;
    puts("Begin!");
    err = pthread_create(&tid,NULL,func,NULL);
    if(err)
    {
        fprintf(stderr,"pthread_create():%s\n",strerror(err));
        exit(1);
    }

    pthread_join(tid,NULL);

    puts("end");
    exit(0);
}