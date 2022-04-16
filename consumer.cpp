
#include "broker.h"
#include "consumer.h"
#include "shared_data.h"

void* consumer::consume(void *args){
    struct shared_data *DATA = (shared_data*)args;
    for(int i = 0; i < 3; i++){

        sem_wait(DATA->mutex);

        /* CRITICAL SECTION */
        broker *buffer = DATA->buffer;
        buffer->poll();

        sem_post(DATA->mutex);
    }
    return NULL;
}