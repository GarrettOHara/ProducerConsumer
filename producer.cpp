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
        /* STOP REQUESTS, LIMIT REACHED */
        if(DATA->current_requests >= DATA->request_limit) { break; }

        /* PROCESS LATENCY */
        sleep(1);

        sem_wait(DATA->mutex);

        /* CRITICAL SECTION */
        bool human = DATA->sleep_time == DATA->human_driver_req;
        broker *buffer = DATA->buffer;
        if(buffer->offer(human))
            DATA->current_requests++;
        
        printf("PUSH: %s\n", human ? "human" : "auton");

        sem_post(DATA->mutex);
    }
    printf("PRODUCER KILLED\n");
    return NULL;
}