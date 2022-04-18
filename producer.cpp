/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | April 2022
 **/
#include <unistd.h>
#include <semaphore.h>

#include "broker.h"
#include "producer.h"
#include "shared_data.h"

void* producer::produce(void* args){
    struct shared_data *DATA = (shared_data*)args;
    while(true){
    // for(int i = 0; i < 10; i++){
        sleep(1);
        sem_wait(DATA->mutex);

        /* CRITICAL SECTION */
        broker *buffer = DATA->buffer;
        buffer->offer(i);

        sem_post(DATA->mutex);
    }
    return NULL;
}