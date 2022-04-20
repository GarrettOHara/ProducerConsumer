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
#define SEM_RESOURCE 0
#define MUTEX_RESOURCE 1


using namespace std;

/**
 * @brief set the threading data object
 * 
 * @param DATA    CLI arguments struct
 * @param a       human producer thread
 * @param b       robot producer thread
 * @param c       cost saving algo thread
 * @param d       fast match algo thread
 * @param buffer  pointer to broker object
 * @param mutex   pointer to binary semaphore
 * @param main    pointer to main thread semaphore
 */
void set_threading_data(struct arguments *DATA,
    threading_data *a,
    threading_data *b, 
    threading_data *c,
    threading_data *d,
    broker *buffer,
    sem_t *mutex,
    sem_t *human_req,
    sem_t *robot_req,
    sem_t *cost_algo,
    sem_t *fast_algo){
    
    /* SET POINTER TO BROKER OBJ FOR EACH THREAD */
    a->buffer = buffer;
    b->buffer = buffer;
    c->buffer = buffer;
    d->buffer = buffer;
    
    /* SET POINTER TO MUTEX SEMAPHORE FOR EACH THREAD*/
    a->mutex = mutex;
    b->mutex = mutex;
    c->mutex = mutex;
    d->mutex = mutex;

    /* SET POINTER TO THREAD SEMAPHORE RESPECTIVELY */
    a->human_req = human_req;
    b->robot_req = robot_req;
    c->cost_algo = cost_algo;
    d->fast_algo = fast_algo;

    /* SET POINTER TO ARGUMENTS STRUCT FOR EACH THREAD */
    b->args = DATA;
    a->args = DATA;
    c->args = DATA;
    d->args = DATA;
    
    /* SET LATENCY RESPECTIVLEY*/
    a->latency = DATA->human_driver_req;
    b->latency = DATA->auton_driver_req;
    c->latency = DATA->cost_saving_consumer;
    d->latency = DATA->fast_match_consumer;

    /* SET THREAD ID RESPECTIVELY */
    a->id = HUMAN_REQ_ID;
    b->id = AUTON_REQ_ID;
    c->id = COST_ALGO_ID;
    d->id = FAST_ALGO_ID;
}

/**
 * @brief driver of program
 * - initalize objects
 * - spawn and manage child threads
 * 
 * @param arc  CLI argument count
 * @param argv pointer to arguments
 * @return int NULL
 */
int main(int arc, char **argv){
    try{

        /* INSTANTIATE SEMAPHORES */
        sem_t mutex, human_req, robot_req, cost_algo, fast_algo;
        sem_init(&mutex, 0, MUTEX_RESOURCE);
        sem_init(&human_req,  0, SEM_RESOURCE);
        sem_init(&robot_req,  0, SEM_RESOURCE);
        sem_init(&cost_algo,  0, SEM_RESOURCE);
        sem_init(&fast_algo,  0, SEM_RESOURCE);


        /* INSTANTIATE BROKER */
        broker *bounded_buffer = new broker;


        /* INSTANTIATE SHARED DATA STRUCTURE AND EXTRACT CLI ARGUMENTS */
        struct arguments DATA;
        args::proccess_args(arc, argv, &DATA);


        /* PAIR LATENCY DATA WITH THREAD */
        threading_data prodA, prodB, consA, consB;
        set_threading_data(&DATA,
            &prodA,
            &prodB,
            &consA,
            &consB,
            bounded_buffer,
            &mutex,
            &human_req,
            &robot_req,
            &cost_algo,
            &fast_algo);
        

        /* INSTANTIATE THREADS */
        pthread_t producerA, producerB, consumerA, consumerB;
        

        /* CREATE PRODUCER CONSUMER THREADS WITH RESPECTIVE PROCESS LATENCY*/
        pthread_create(&producerA,NULL,producer::produce,&prodA);
        pthread_create(&producerB,NULL,producer::produce,&prodB);
        pthread_create(&consumerA,NULL,consumer::consume,&consA);
        pthread_create(&consumerB,NULL,consumer::consume,&consB);


        /* WAIT FOR ALL THREAD PROCESSES TO FINISH */
        sem_wait(&human_req);
        sem_wait(&robot_req);
        sem_wait(&cost_algo);
        sem_wait(&fast_algo);

        /* {TOTAL HUMAN REQUESTS PRODUCED, TOTAL AUTONOMOUS REQUETS PRODUCED} */
        int produced[] = {bounded_buffer->total_human_reqs,
            bounded_buffer->total_requests-bounded_buffer->total_human_reqs};
        
        /* CAST 2D VECTOR TO *int[] */
        int *consumed[2];
        *consumed = bounded_buffer->consumed[0].data();
        *(consumed + 1) = bounded_buffer->consumed[1].data();

        /* PRINT PROGRAM SUMMARY */
        io_production_report(produced,consumed);
        

        /* FREE SEMAPHORE MEMORY */
        sem_destroy(&mutex);
        sem_destroy(&human_req);
        sem_destroy(&robot_req);
        sem_destroy(&cost_algo);
        sem_destroy(&fast_algo);
        
    } catch ( const exception& e ) {
        cerr << "ERROR: " << e.what() << endl;
    } catch (...) {
        cout << "Exception occurred";
    }
}