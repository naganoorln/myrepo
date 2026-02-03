#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
pthread_mutex_t mtx;
pthread_cond_t cond;
int is_empty = 1;
int buffer = 0;
void* producer(void* arg)
{
    int item = 0;
    while(1)
    {
        pthread_mutex_lock(&mtx);
        while(!is_empty)
        {
            pthread_cond_wait(&cond, &mtx);
        }
        buffer = ++item;
        is_empty = 0;
        printf("Prduced: %d\n", buffer);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx);
        sleep(1);
    }
    return NULL;
}
void* consumer(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&mtx);
        while(is_empty)
        {
            pthread_cond_wait(&cond, &mtx);
        }
        printf("Consumed: %d\n", buffer);
        is_empty = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx);
        sleep(2);
    }
    return NULL;
}
int main()
{
    pthread_t pthd;
    pthread_t cthd;
    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_create(&pthd, NULL, producer, NULL);
    pthread_create(&cthd, NULL, consumer, NULL);
    pthread_join(pthd, NULL);
    pthread_join(cthd, NULL);
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond);
    return 0;
}