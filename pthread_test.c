
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/select.h>
#include "thpool.h"
struct share_data {
    int i;
};

void ssleep(long sec,long usec)
{
    struct timeval tv;
    tv.tv_sec=sec;
    tv.tv_usec = usec;
    select(0, NULL, NULL, NULL, &tv);
}

pthread_mutex_t mutex_serial_share_data;
void read_serial(void *arg){
    struct share_data *data = (struct share_data *)arg;
	printf("Thread #%u name: %s\n", (int)pthread_self(), __func__);
    while(1){
        pthread_mutex_lock(&mutex_serial_share_data);
        printf("%s: data: %d\n", __func__, data->i);
        data->i++;
        printf("%s: data: %d\n", __func__, data->i);
        data->i++;
        pthread_mutex_unlock(&mutex_serial_share_data);
        ssleep(0, 1000*500);
    }
}

void get_serial_data(void *arg){
    struct share_data *data = (struct share_data *)arg;
	printf("Thread #%u name: %s\n", (int)pthread_self(), __func__);
    while(1){
        pthread_mutex_lock(&mutex_serial_share_data);
        printf("%s: data: %d\n", __func__, data->i);
        data->i++;
        printf("%s: data: %d\n", __func__, data->i);
        data->i++;
        pthread_mutex_unlock(&mutex_serial_share_data);
        ssleep(0, 1000*500);
    }
}

int main(int argc, char **argv)
{
    struct share_data data = {0};
    threadpool thpool = thpool_init(3);
    pthread_mutex_init(&mutex_serial_share_data, NULL);
    thpool_add_work(thpool, read_serial, (void*)(uintptr_t)&data);
    thpool_add_work(thpool, get_serial_data, (void*)(uintptr_t)&data);
    //thpool_add_work(thpool, get_serial_data, (void*)(uintptr_t)&data);
    thpool_wait(thpool);
    thpool_destroy(thpool);
    return 0;
}