#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


static void *func(void *p)
{
    puts("thread is workding");
    //return NULL;
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
        fprintf(stderr,"pthread_create(): %s",strerror(err));
        exit(1);
    }

    pthread_join(tid,NULL);

    puts("end");
    exit(0);
}