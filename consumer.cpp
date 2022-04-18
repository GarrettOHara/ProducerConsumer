/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | April 2022
 **/
#include <unistd.h>
#include "broker.h"
#include "consumer.h"
#include "shared_data.h"

void* consumer::consume(void *args){
    struct shared_data *DATA = (shared_data*)args;
    while(true){

        /* PROCESS LATENCY */
        sleep(1);
        sem_wait(DATA->mutex);

        /* CRITICAL SECTION */
        broker *buffer = DATA->buffer;
        if(DATA->current_requests >= DATA->request_limit &&
            buffer->current_size == 0) { sem_post(DATA->mutex); break; }

        if(buffer->poll()){
            printf("POLL:\t%d\t%d\t%d\t%d\n",
                DATA->current_requests,
                DATA->request_limit,
                buffer->current_size,
                buffer->current_human_reqs);
        }
        sem_post(DATA->mutex);
    }
    printf("CONSUMER KILLED\n");
    return NULL;
}