#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// shared data
int is_data_available = 0;
int buffer = 0;
// mutex and conditional variables
pthread_mutex_t mtx;
pthread_cond_t cond_var_produce;
pthread_cond_t cond_var_consume;

// producer thread
void* producer(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&mtx);
        // Wait if there is data that has not been consumed
        while(is_data_available)
        {
            pthread_cond_wait(&cond_var_consume, &mtx);
        }
        buffer = rand() % 100;
        is_data_available = 1;
        printf("Data is produced: %d\n",buffer);
        // signal the consumer that data is available
        pthread_cond_signal(&cond_var_produce);
        pthread_mutex_unlock(&mtx);
        sleep(1);
    }
    return NULL;
}

// consumer thread
void* consumer(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&mtx);
        // wait for the data to be produced by producer
        while(!is_data_available)
        {
            pthread_cond_wait(&cond_var_produce, &mtx);
        }
        printf("Data consumed: %d\n",buffer);
        is_data_available = 0;
        // signal the producer that data has been consumed
        pthread_cond_signal(&cond_var_consume);
        pthread_mutex_unlock(&mtx);
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t pthdid, cthdid;
    // initialize mutex and conditional variables
    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&cond_var_produce, NULL);
    pthread_cond_init(&cond_var_consume, NULL);
    // create producer/consumer threads
    pthread_create(&pthdid, NULL, producer, NULL);
    pthread_create(&cthdid, NULL, consumer, NULL);
    pthread_join(pthdid, NULL);
    pthread_join(cthdid, NULL);
    // destroy mutex and conditional variables
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond_var_produce);
    pthread_cond_destroy(&cond_var_consume);
    return 0;
}
