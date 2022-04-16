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
#include "ridesharing.h"
#include "shared_data.h"

using namespace std;

sem_t mutex;

void* produce(void* args){

    for(int i = 0; i < 10; i++){

        sem_wait(&mutex);

        /* CRITICAL SECTION */
        broker *buffer = (broker*)args;
        buffer->offer(i);

        sem_post(&mutex);

    }

    
    return NULL;
}

void* consume(void* args){

    for(int i = 0; i < 10; i++){
        sem_wait(&mutex);

        /* CRITICAL SECTION */
        broker *buffer = (broker*)args;
        buffer->poll();

        sem_post(&mutex);

    }

    return NULL;
}

int main(int arc, char **argv){
    try{
        /* INSTANTIATE SHARED DATA STRUCTURE */
        struct shared_data DATA;

        /* INSTANTIATE BINARY SEMAPHORE */
        sem_init(&mutex, 0, 1);
        
        /* INSTANTIATE THREADS */
        pthread_t threads[2];
        pthread_t producer, consumer;

        /* INSTANTIATE BROKER */
        broker *bounded_buffer = new broker;

        /* SET SHARED DATA POINTERS */
        DATA.mutex  = &mutex;
        DATA.buffer = bounded_buffer;

        /* CREATE PRODUCER CONSUMER THREADS */
        pthread_create(&producer,NULL,producer::produce,&DATA);
        pthread_create(&consumer,NULL,consumer::consume,&DATA);
        
        // calls are not ground together here 
        // pthread_create(&producer,NULL,&produce,bounded_buffer);
        // pthread_create(&consumer,NULL,&consume,bounded_buffer);
        
        /* JOIN THREADS */
        pthread_join(producer,NULL);
        pthread_join(consumer,NULL);

        /* FREE SEMAPHORE MEMORY */
        sem_destroy(&mutex);

    } catch ( const exception& e ) {
        cerr << "ERROR: " << e.what() << endl;
    } catch (...) {
        cout << "Exception occurred";
    }
}