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
#define HUMAN_ID 0

/**
 * @brief produce requests and insert into
 * request buffer
 * 
 * @param args pointer to thread argument
 *  - pass pointer to threading_data struct
 * @return void* 
 */
void* producer::produce(void* args){
    
    /* CAST PARAMETER */
    threading_data *thread_data = (threading_data*)args;
    broker *buffer = thread_data->buffer;

    while(true){

        /* PROCESS LATENCY */
        usleep(thread_data->latency*CAST);
        
        /* CRITICAL SECTION */
        sem_wait(thread_data->mutex);

        /* STOP REQUESTS WHEN LIMIT REACHED */
        if(buffer->total_requests >= thread_data->args->request_limit) { 
            sem_post(thread_data->mutex);
            break;
        }

        /* DETERMINE TYPE OF REQUEST */
        bool human = thread_data->id == HUMAN_ID;

        /* ONLY WRITE TO STD OUT IF INSERT SUCCESSFUL */
        if(buffer->offer(human)){
            
            /* {HUMAN REQUESTS IN BUFFER, ROBOT REQUESTS IN BUFFER} */
            int request_queue[] = {buffer->current_human_reqs,buffer->current_requests-buffer->current_human_reqs};

            /* {TOTAL HUMAN REQUESTS, TOTAL ROBOT REQUETS } */
            int produced[] = {buffer->total_human_reqs,buffer->total_requests-buffer->total_human_reqs};

            /* OUTPUT */
            io_add_type(RequestType (thread_data->id), request_queue, produced);
        }

        /* UNLOCK CRITICAL SECTION */
        sem_post(thread_data->mutex);
    }
    if(thread_data->id==HUMAN_ID)
        sem_post(thread_data->human_req);
    else
        sem_post(thread_data->robot_req);
    return NULL;
}