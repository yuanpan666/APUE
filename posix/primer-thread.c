#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>

#define LEFT  30000000
#define RIGHT 30000200
#define THRNUM (RIGHT-LEFT+1)


static void *thr_prime(void *p)
{
    int mark,i;
    i = (int )p;

     mark = 1;
       for (int j = 2; j < i/2; j++)
       {
           /* code */

           if(i%j == 0)
           {
               mark = 0;
               break;
           }
       }
       if(mark)
            printf("%d is a primer\n",i);
    
    pthread_exit(NULL);


  
}


int main(void)
{
   pid_t pid;
   int i,j,err;
   pthread_t tid[THRNUM];

    for(i=LEFT;i<=RIGHT;i++)
    {
        err = pthread_create(tid+i-LEFT,NULL,thr_prime,(void*)i);
        if(err)
        {
            fprintf(stderr,"thread create() error%s\n",strerror(err));
            exit(1);
        }
    }

    for(i=LEFT;i<=RIGHT;i++)
    {
        pthread_join(tid[i-LEFT],NULL);
    }   


    exit(EXIT_SUCCESS);
}


