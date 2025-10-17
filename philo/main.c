#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define ITERATION 10000000
#define THREAD_COUNT 16

pthread_t threads[THREAD_COUNT];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

#if 0
int count = 0;

void *routine()
{
	pthread_mutex_lock(&mutex);
	for (int i = 0; i < ITERATION; i++)
		count++;
	pthread_mutex_unlock(&mutex);
	return NULL;
}
#else

_Atomic int count = 0;
void *routine()
{
	for (int i = 0; i < ITERATION; i++)
		count++;
	return NULL;
}

#endif

int main(void)
{
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		pthread_create(&threads[i], NULL, routine, NULL);
	}
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		pthread_join(threads[i], NULL);
	}
	printf("count: %d\n", count);
	return 0;
}
