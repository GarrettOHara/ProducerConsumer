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
#define VALUE_INDEX 0
#define REQUEST_INDEX 1

void* consumer::consume(void *args){
    threading_data *thread_data = (threading_data*)args;
    broker *buffer = thread_data->buffer;
    while(true){

        /* PROCESS LATENCY */
        sleep(thread_data->latency/CAST);
        
        /* CRITICAL SECTION */
        sem_wait(thread_data->mutex);

        /* KEEP POLLING UNTIL TOTAL REQUESTS MET AND BUFFER IS EMPTY */
        if(buffer->total_requests >= thread_data->args->request_limit &&
            buffer->current_requests == 0) { sem_post(thread_data->mutex); break; }

        /* RETURNS TRUE IF REQUEST POLLED */
        bool *arr = buffer->poll();
        
        if(arr[VALUE_INDEX]){
            printf("\nRETURED DATA: %d   %d\n",int(arr[VALUE_INDEX]), int(arr[REQUEST_INDEX]));
            int in_request_queue[] = {buffer->current_requests-buffer->current_human_reqs,buffer->current_human_reqs};
            int consumed[] = {buffer->consumed_requests-buffer->consumed_human_reqs, buffer->consumed_human_reqs};
            io_remove_type(Consumers (thread_data->id),
                RequestType (arr[REQUEST_INDEX]),
                in_request_queue,
                consumed);

            /* UPDATE REPORT VALUES */
            buffer->consumed[int(arr[VALUE_INDEX])][thread_data->id]++;
            
            /* DEUG */
            // printf("POLL\tCURRENT REQUESTS: %d"
            //        "\tREQUEST LIMIT: %d"
            //        "\tCURRENT HUMAN REQS: %d\n",
            //     buffer->current_requests,
            //     thread_data->args->request_limit,
            //     buffer->current_human_reqs);
        }
        sem_post(thread_data->mutex);
        
        
    }
    return NULL;
}