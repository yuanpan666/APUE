#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


#define THRUM  20
#define FNAME "/tmp/out"
#define LINESIZE 1024
static void *thr_add(void *p)
{
  FILE *fp;
  char linebuf[LINESIZE];
  fp = fopen(FNAME,"r+");
  if(fp == NULL)
  {
    perror("fopen()");
    exit(1);
  }
  

  fgets(linebuf,LINESIZE,fp);
  fseek(fp,0,SEEK_SET);
  fprintf(fp,"%d\n",atoi(linebuf) + 1);

  fclose(fp);

  pthread_exit(NULL);
}

int main()
{
  pthread_t tid[THRUM];
  for(int i=0; i < THRUM; i++)
  {
    int err = pthread_create(tid+i,NULL,thr_add,NULL);
    if(err)
    {
      fprintf(stderr,"pthread_create():%s",strerror(err));
      exit(1);
    }
  }

  for(int i=0;i < THRUM; i++)
  {
    pthread_join(tid[i],NULL);
  }


  exit(0);
}