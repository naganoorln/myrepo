#include <stdio.h>
#include <pthread.h>
#define MAX 10
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int num = 1;
int consumed = 1;
void* producer(void* arg)
{
    while(num <= MAX)
    {
        pthread_mutex_lock(&mtx);
        pthread_cond_signal(&cond);
        while(consumed)
        {
            pthread_cond_wait(&cond, &mtx);
        }
        num++;
        consumed = 1;
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}
void* consumer(void* arg)
{
    while(num <= MAX)
    {
        pthread_mutex_lock(&mtx);
        while(!consumed)
        {
            pthread_cond_wait(&cond, &mtx);
        }
        printf("%d\n",num);
        consumed = 0;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}
int main()
{
    pthread_t pthd, cthd;
    pthread_create(&pthd, NULL, producer, NULL);
    pthread_create(&cthd, NULL, consumer, NULL);
    pthread_join(pthd, NULL);
    pthread_join(cthd, NULL);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mtx);
    return 0;
}
