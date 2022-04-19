/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | April 2022
 **/
#include <vector>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <stdexcept>
#include <semaphore.h>

#include "io.h"
#include "broker.h"
#include "consumer.h"
#include "producer.h"
#include "arguments.h"
#include "ridesharing.h"
#include "thread_data.h"

#define HUMAN_REQ_ID 0
#define AUTON_REQ_ID 1
#define COST_ALGO_ID 0
#define FAST_ALGO_ID 1
#define THREAD_COUNT 4
#define SEM_RESOURCE 1

using namespace std;

void set_threading_data(struct arguments *DATA,
    threading_data *a,
    threading_data *b, 
    threading_data *c,
    threading_data *d,
    broker *buffer,
    sem_t *mutex){
    
    a->buffer = buffer;
    b->buffer = buffer;
    c->buffer = buffer;
    d->buffer = buffer;

    a->mutex = mutex;
    b->mutex = mutex;
    c->mutex = mutex;
    d->mutex = mutex;

    b->args = DATA;
    a->args = DATA;
    c->args = DATA;
    d->args = DATA;
    
    a->latency = DATA->human_driver_req;
    b->latency = DATA->auton_driver_req;
    c->latency = DATA->cost_saving_consumer;
    d->latency = DATA->fast_match_consumer;

    a->id = HUMAN_REQ_ID;
    b->id = AUTON_REQ_ID;
    c->id = COST_ALGO_ID;
    d->id = FAST_ALGO_ID;
}

int main(int arc, char **argv){
    try{

        /* INSTANTIATE BINARY SEMAPHORE */
        sem_t mutex;
        sem_init(&mutex, 0, SEM_RESOURCE);


        /* INSTANTIATE BROKER */
        broker *bounded_buffer = new broker;


        /* INSTANTIATE SHARED DATA STRUCTURE AND EXTRACT CLI ARGUMENTS */
        struct arguments DATA;
        args::proccess_args(arc, argv, &DATA);


        /* PAIR LATENCY DATA WITH THREAD */
        threading_data prodA, prodB, consA, consB;
        set_threading_data(&DATA,&prodA,&prodB,&consA,&consB,bounded_buffer,&mutex);
        

        /* INSTANTIATE THREADS */
        pthread_t producerA, producerB, consumerA, consumerB;
        

        /* CREATE PRODUCER CONSUMER THREADS WITH RESPECTIVE PROCESS LATENCY*/
        pthread_create(&producerA,NULL,producer::produce,&prodA);
        pthread_create(&producerB,NULL,producer::produce,&prodB);
        pthread_create(&consumerA,NULL,consumer::consume,&consA);        
        pthread_create(&consumerB,NULL,consumer::consume,&consB);


        /* WAIT FOR ALL THREAD PROCESSES TO FINISH */
        pthread_join(producerA,NULL);
        pthread_join(producerB,NULL);
        pthread_join(consumerA,NULL);
        pthread_join(consumerB,NULL);

        /* PROGRAM REPORT */
        int produced[] = {bounded_buffer->total_human_reqs,
            bounded_buffer->total_requests-bounded_buffer->total_human_reqs};
        
        io_production_report(produced,bounded_buffer->consumed);
        

        /* FREE SEMAPHORE MEMORY */
        sem_destroy(&mutex);

        exit(0);

    } catch ( const exception& e ) {
        cerr << "ERROR: " << e.what() << endl;
    } catch (...) {
        cout << "Exception occurred";
    }
}