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

using namespace std;

sem_t mutex;

void* produce(void* args){
    sem_wait(&mutex);

    /* CRITICAL SECTION */
    sleep(3);
    broker buffer = *(broker*)args;
    buffer.offer(1);
    buffer.to_string();
    printf("\n");

    sem_post(&mutex);
    return NULL;
}

void* consume(void* args){
    sem_wait(&mutex);

    /* CRITICAL SECTION */
    sleep(0.1);
    broker buffer = *(broker*)args;
    buffer.poll(1,9);
    buffer.to_string();
    printf("\n");

    sem_post(&mutex);
    return NULL;
}

int main(int arc, char **argv){
    try{

        /* INSTANTIATE BINARY SEMAPHORE */
        sem_init(&mutex, 0, 1);
        
        /* INSTANTIATE THREADS */
        pthread_t threads[2];
        pthread_t producer, consumer;

        /* INSTANTIATE BROKER */
        broker *bounded_buffer = new broker;

        bounded_buffer->to_string();
        printf("\n");

        pthread_create(&producer,NULL,&produce, bounded_buffer);
        pthread_create(&consumer,NULL,&consume,bounded_buffer);
        

        pthread_join(producer,NULL);
        pthread_join(consumer,NULL);

        // pthread_create(&threads[i], NULL, &produce, bounded_buffer);
    
        // pthread_join(threads[i], NULL);
        
        /* FREE SEMAPHORE MEMORY */
        sem_destroy(&mutex);

    } catch ( const exception& e ) {
        cerr << "ERROR: " << e.what() << endl;
    } catch (...) {
        cout << "Exception occurred";
    }
}