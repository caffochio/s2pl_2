#include "concurrency.h"

DATA DataObj[MAX_OBJ];

void
my_sort(int access[])
{
  for (int j=1; j<MAX_OPERATION; j++)
  {
    int key = access[j];
    int i = j-1;
    while (i>=0 && access[i]>key)
    {
      access[i+1] = access[i];
      i = i-1;
      access[i+1] = key;
    }
    
  }

  // Sort Checker
  for (int i = 0; i < MAX_OPERATION-1; i++)
  {
    if (access[i+1] < access[i])
    {
      printf ("Sorting Failed\n");
      break;
    }
  }
  printf ("Sorting Succeeded\n");

}

typedef struct _OPERATION
  {
    int access_id;
    int value;
  } OPRT;

typedef struct _WORKER
{
  OPRT oprt;
} WORKER;

WORKER
make_operation()
{
  WORKER worker
  for (int i=0; i<MAX_OPERATION; i++)
  {
    worker.oprt[i].access = rand() % MAX_OBJ;
    worker.oprt[i].value = rand();
  }
  return worker;
}

void
make_worker()
{
  WORKER worker[nthread]
  for (int i=0; i<nthread; i++)
  {
    worker[i] = make_operation();
  }
}

void
task(OPRT o)
{
  DataObj[o.access] = o.value;
}



static void *
worker(void *arg)
{


  // Sort
  my_sort(access);

  /* Growing Phase */
  for (int i = 0; i < MAX_OPERATION-1; i++) {
		if (access[i] != access[i+1])
    {
      lock(access[i]);
    }
  }

  for (int i = 0; i < MAX_OPERATION; i++) {
		if (access[i] != access[i+1])
    {
      task(worker[wid].oprt[i]);
    }
  }
	
	/* Shrinking Phase */
  for (int i = 0; i < MAX_OPERATION; i++) {
		if (access[i] != access[i+1])
    {
      unlock(access[i]);
    }
	}

  return NULL;
}

extern int
main(int argc, char *argv[])
{
  int i, nthread = 4;
  struct timeval begin, end;
	pthread_t *thread;
	
	if (argc == 2) nthread = atoi(argv[1]);
	thread = (pthread_t *)calloc(nthread, sizeof(pthread_t));
	if (!thread) ERR;
	
	gettimeofday(&begin, NULL);
  for (i = 0; i < nthread; i++) {
    int *wid = (int*)calloc(1, sizeof(int));
    int ret = pthread_create(&thread[i], NULL, worker, (void*)wid);
		if (ret < 0) ERR;
	}

  for (i = 0; i < nthread; i++) {
		int ret = pthread_join(thread[i], NULL);
		if (ret < 0) ERR;
	}
  gettimeofday(&end, NULL);
  print_result(begin, end, nthread);
	free(thread);
	
  return 0;
}
