#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM 4

static int num = 0;
static pthread_mutex_t mut_num = PTHREAD_MUTEX_INITIALIZER;

static void *thr_prime(void *p)
{
  int mark, i;
  i = num;

  mark = 1;

  while (1)
  {
    pthread_mutex_lock(&mut_num);
    while (num == 0)
    {
      pthread_mutex_unlock(&mut_num);
      sched_yield();
      pthread_mutex_lock(&mut_num);
    }
    if (num == -1)
    {
      pthread_mutex_unlock(&mut_num);
      break;
    }

    i = num;
    num = 0;
    pthread_mutex_unlock(&mut_num);

    for (int j = 2; j < i / 2; j++)
    {
      /* code */

      if (i % j == 0)
      {
        mark = 0;
        break;
      }
    }
    if (mark)
      printf("[%d]%d is a primer\n",(int)p, i);
  }

  pthread_exit(NULL); // p is the location, and the return value
}

int main(void)
{

  int i, err;

  pthread_t tid[THRNUM];



  for (i = 0; i < THRNUM; i++)
  {
    err = pthread_create(tid + i, NULL, thr_prime, (void *)i);
    if (err)
    {
      fprintf(stderr, "thread create() error%s\n", strerror(err));
      exit(1);
    }
  }

  for (i = LEFT; i <= RIGHT; i++)
  {
    pthread_mutex_lock(&mut_num);

    while (num != 0)
    {
      pthread_mutex_lock(&mut_num);
      sched_yield();
      pthread_mutex_unlock(&mut_num);
    }
    num = i;
    pthread_mutex_unlock(&mut_num);
  }

  pthread_mutex_lock(&mut_num);
  while (num != 0)
  {
    pthread_mutex_lock(&mut_num);
    sched_yield();
    pthread_mutex_unlock(&mut_num);
  }

  num = -1;
  pthread_mutex_unlock(&mut_num);

  for (i = 0; i <= THRNUM; i++)
  {
    pthread_join(tid[i], NULL);
  }

  pthread_mutex_destroy(&mut_num);
  exit(EXIT_SUCCESS);
}
