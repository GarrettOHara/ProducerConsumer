#include <semaphore.h>

#include "broker.h"
#include "producer.h"
#include "shared_data.h"

void* producer::produce(void* args){
    struct shared_data *DATA = (shared_data*)args;
    for(int i = 0; i < 10; i++){

        sem_wait(DATA->mutex);

        /* CRITICAL SECTION */
        broker *buffer = DATA->buffer;
        buffer->offer(i);

        sem_post(DATA->mutex);
    }
    return NULL;
}