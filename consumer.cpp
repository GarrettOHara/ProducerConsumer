/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | April 2022
 **/
#include <unistd.h>

#include "io.h"
#include "broker.h"
#include "consumer.h"
#include "thread_data.h"
#include "ridesharing.h"

#define CAST 1000
#define INSERT_COMPLETE 0
#define REQUEST_INDEX 1
#define COST_SAVING_ALGO 0
#define FAST_MATHCHING_ALO 1

/**
 * @brief consume requests from bounded buffer
 * 
 * @param args pointer to thread argument
 *  - pass pointer to threading_data struct
 * @return void* 
 */
void* consumer::consume(void *args){
    /* CAST PARAMETER */
    threading_data *thread_data = (threading_data*)args;
    broker *buffer = thread_data->buffer;
    while(true){

        /* PROCESS LATENCY */
        usleep(thread_data->latency*CAST);
        
        /* CRITICAL SECTION */
        sem_wait(thread_data->mutex);

        /* KEEP POLLING UNTIL TOTAL REQUESTS MET AND BUFFER IS EMPTY */
        if(buffer->total_requests >= thread_data->args->request_limit &&
            buffer->current_requests == 0) { sem_post(thread_data->mutex); break; }

        /* RETURNS TRUE IF REQUEST POLLED */
        /* arr[REQUEST SUCCESS][REQUEST TYPE] */
        bool *arr = buffer->poll();
        
        /* IF REQUEST WAS SUCCESSFUL, UPDATE COUNTS, WRITE TO STD OUT */
        if(arr[INSERT_COMPLETE]){
            
            /* BUFFER->CONSUMED: vector[ALGORITHM][REQUEST TYPE] 0:HDR 1:RDR */
            int request_indx = 0;
            if(!arr[REQUEST_INDEX])
                request_indx = 1;
            buffer->consumed[thread_data->id][request_indx]++;
            
            /* request{BUFFER TOTAL REQUESTS, BUFFER TOTAL HUMAN REQUESTS}*/
            int request[] = {buffer->current_requests-buffer->current_human_reqs,
                buffer->current_human_reqs};
            
            /* consumed{COST SAVING ALGORITHM FOR REQUEST X, 
                FAST MATCHING ALGORITHM FOR REQUEST X} */
            int consumed[] = {buffer->consumed[arr[REQUEST_INDEX]][COST_SAVING_ALGO],
                buffer->consumed[arr[REQUEST_INDEX]][FAST_MATHCHING_ALO]};
            
            /* WRITE TO STD OUT */
            io_remove_type(Consumers (thread_data->id),
                RequestType (arr[REQUEST_INDEX]),
                request,
                consumed);
        }

        /* UNLOCK CRITICAL SECTION */
        sem_post(thread_data->mutex);
    }

    /* SIGNAL MAIN THREAD */
    if(thread_data->id==COST_SAVING_ALGO)
        sem_post(thread_data->cost_algo);
    else
        sem_post(thread_data->fast_algo);
    return NULL;
}