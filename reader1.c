#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
sem_t mutex,writerblock;
int rcount=0,data=0;
void *reader(void*arg){
	int f;
	f=((int)arg);
	sem_wait(&mutex);
	rcount++;
	if(rcount==1)
		sem_wait(&writerblock);
	sem_post(&mutex);
	printf("data read by  reader %d is %d",f,data);
	sleep(1);
	sem_wait(&mutex);
	rcount--;
	if(rcount==0)
		sem_post(&writerblock);
	sem_post(&mutex);
}
void *writer(void*arg)
{
	int f;
	f=((int)arg);
	sem_wait(&writerblock);
	data++;
	printf("data written by %d",f);
	sleep(1);
	sem_post(&writerblock);
}
int main()
{
	int i,b;
	pthread_t rid[5],wid[5];
	sem_init(&mutex,0,1);
	sem_init(&writerblock,0,1);
	for(int i=0;i<5;i++)
	{
	pthread_create(&wid[i],NULL,writer,(void *)i);
	pthread_create(&rid[i],NULL,reader,(void *)i);
	}
	for(int i=0;i<5;i++)
	{
	pthread_join(&wid[i],NULL);
	pthread_join(&rid[i],NULL);
	}
	return 0;
}
