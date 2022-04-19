/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | April 2022
 **/
#include <unistd.h>
#include <semaphore.h>

#include "io.c"
#include "broker.h"
#include "producer.h"
#include "thread_data.h"
#include "ridesharing.h"

#define CAST 1000

void* producer::produce(void* args){
    
    threading_data *thread_data = (threading_data*)args;
    broker *buffer = thread_data->buffer;

    while(true){

        /* PROCESS LATENCY */
        usleep(thread_data->latency*CAST);
        
        /* CRITICAL SECTION */
        sem_wait(thread_data->mutex);

        /* STOP REQUESTS, LIMIT REACHED */
        if(buffer->total_requests >= thread_data->args->request_limit) { 
            sem_post(thread_data->mutex);
            break;
        }

        /* DETERMINE TYPE OF REQUEST */
        bool human = thread_data->latency == thread_data->args->human_driver_req;

        /* ONLY WRITE TO STD OUT IF INSERT SUCCESSFUL */
        if(buffer->offer(human)){
            
            /* OUTPUT */
            int request_queue[] = {buffer->current_human_reqs,buffer->current_requests-buffer->current_human_reqs};
            int produced[] = {buffer->total_human_reqs,buffer->total_requests-buffer->total_human_reqs};
            io_add_type(RequestType (thread_data->id), request_queue, produced);

            /* DEBUG */
            // printf("POST\t\t%s\tBUFFER SIZE: %d\tHUMAN REQS: %d\n",
            // human ? "human" : "auton", 
            // buffer->current_requests,
            // buffer->current_human_reqs);
        }

        

        

        sem_post(thread_data->mutex);
        
        
    }
    return NULL;
}