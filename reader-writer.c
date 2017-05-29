#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

int rc=0,wc=0,val;
pthread_mutex_t mutex1,mwrite,mread,rallow;
pthread_t tr,tw;
pthread_attr_t trattr,twattr;

void *writer();

void *reader();

int main()
{
 pthread_mutex_init(&mwrite,NULL);
 pthread_mutex_init(&mread,NULL);
 pthread_mutex_init(&rallow,NULL);
 pthread_mutex_init(&mutex1,NULL);
 pthread_attr_init(&twattr);
 pthread_attr_init(&trattr);
 // pthread_attr_init(&tr2attr);
 // pthread_attr_init(&tw2attr);
 printf("Writer 1 created\n");
 pthread_create(&tw,&twattr,writer,NULL);
 printf("Reader 1 created\n");
 pthread_create(&tr,&trattr,reader,NULL);
 // printf("\n Reader 2 created");
 // pthread_create(&tr2,&tr2attr,reader,NULL);
 // printf("\n WRITER 2 created");
 // pthread_create(&tw2,&tw2attr,writer,NULL);
 
 pthread_join(tw,NULL);
  pthread_join(tr,NULL);
 // pthread_join(tr2,NULL);
 // pthread_join(tw2,NULL);
 return 0;
}

void *writer()
{
	while(1)
	 {pthread_mutex_lock(&mwrite);
	 	 printf("lock mwrite\n");
	 	 wc++;
	 	 if(wc==1)
	 	  	{
	 	  		pthread_mutex_lock(&rallow);
	 	  		printf("lock rallow w\n");
	 	  	}
	 	 pthread_mutex_unlock(&mwrite);
	 	 printf("unlock mwrite\n");
	 	 pthread_mutex_lock(&mutex1);
	 	 printf("lock mutex1 w\n");
	 	 printf("\n Enter data in writer %d\n",wc);
	 	 scanf("%d",&val);
	 	 pthread_mutex_unlock(&mutex1);
	 	 printf("unlock mutex1 w\n");
	 	 pthread_mutex_lock(&mwrite);
	 	 printf("lock mwrite\n");
	 	 wc--;
	 	 if(wc==0)
	 	  	{
	 	  		pthread_mutex_unlock(&rallow);
	 	  	 	printf("unlock rallow w\n");
	 	  	 }
	 	 pthread_mutex_unlock(&mwrite);
	 	 printf("unlock mwrite\n");}
 // pthread_exit(0);
}

void *reader()
{
	while(1)
	 {pthread_mutex_lock(&rallow);
	 	 printf("lock rallow r\n");
	 	 pthread_mutex_lock(&mread);
	 	 printf("lock mread\n");
	 	 rc++;
	 	 if(rc==1)
	 	 {
	 	  	pthread_mutex_lock(&mutex1);
	 	  	printf("lock mutex1 r\n");
	 	 }
	 	 pthread_mutex_unlock(&mread);
	 	 printf("unlock mread\n");
	 	 pthread_mutex_unlock(&rallow);
	 	 printf("unlock rallow r\n");
	 	 printf("\n reader %d read data: %d\n",rc,val);
	 	 pthread_mutex_lock(&mread);
	 	 printf("lock mread\n");
	 	 rc--;
	 	 if(rc==0)
	 	 {
	 	  	pthread_mutex_unlock(&mutex1);
	 	 	printf("unlock mutex1 r\n");
	 	}
	 	 pthread_mutex_unlock(&mread);
	 	 printf("unlock mread\n");}
 // pthread_exit(0);
}