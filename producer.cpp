#include "producer.h"

void* producer::produce(void* args){
    for(int i = 0; i < 10; i++){

        sem_wait(&mutex);

        /* CRITICAL SECTION */
        broker *buffer = (broker*)args;
        buffer->offer(i);

        sem_post(&mutex);
    }
    return NULL;
}