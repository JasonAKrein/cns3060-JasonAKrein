#include <stdlib.h>
#include <stdio.h>
#include <string.h>  
#include <pthread.h>

int count = 0;

int main ()
{
  void *incrementCounter (void*);
  pthread_t t1, t2, t3, t4;

  pthread_create(&t1, NULL, incrementCounter, NULL);
  pthread_create(&t2, NULL, incrementCounter, NULL);
  pthread_create(&t3, NULL, incrementCounter, NULL);
  pthread_create(&t4, NULL, incrementCounter, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  pthread_join(t4, NULL);

  printf("count = %d\n", count);
  return 0;
}


void *incrementCounter (void* m)
{
  int i;
  for ( i = 0; i < 10; ++i)
  {
    int tempValue = count; 
    tempValue = tempValue +1;
    count = tempValue;
  }
  return NULL;
} 
