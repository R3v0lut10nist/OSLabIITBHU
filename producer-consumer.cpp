#include<iostream>
#include<queue>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#define MAX 15
using namespace std;

pthread_mutex_t the_mutex;
queue<int> q;
bool finished=false;

void* producer(void *ptr) {
    for (int i = 1; i <= MAX; i++) {
        pthread_mutex_lock(&the_mutex);
        q.push(i);
        cout<<"Producer Produce "<<i<<endl;
        pthread_mutex_unlock(&the_mutex);
    }
    finished=true;
    pthread_exit(0);
}

void* consumer(void *ptr) {
  while(true){
    pthread_mutex_lock(&the_mutex);
    // while(!q.empty()){
    if(!q.empty())
       { cout<<"Consumer Consume "<<q.front()<<endl;
        q.pop();}
    // }
    pthread_mutex_unlock(&the_mutex);
    sleep(1);
    if(finished && q.empty())break;
  }
  pthread_exit(0);
}

int main(int argc, char **argv) {
  pthread_t pro, con;

  pthread_mutex_init(&the_mutex, NULL);
  
  pthread_create(&con, NULL, consumer, NULL);
  pthread_create(&pro, NULL, producer, NULL);

  pthread_join(con, NULL);
  pthread_join(pro, NULL);


  pthread_mutex_destroy(&the_mutex);
}
