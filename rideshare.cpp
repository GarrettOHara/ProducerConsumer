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
    sleep(1);

    /* CRITICAL SECTION */
    broker tmp = *(broker*)args;
    tmp.offer(1);
    tmp.to_string();
    printf("\n");
    sem_post(&mutex);
    return NULL;
}

void* consume(void* args){
    sem_wait(&mutex);
    sleep(1);
    printf("Hello from %d\n", *(int*)args);
    sem_post(&mutex);
    return NULL;
}

int main(int arc, char **argv){
    try{

        /* INSTANTIATE BINARY SEMAPHORE */
        sem_init(&mutex, 0, 1);
        
        /* INSTANTIATE THREADS */
        pthread_t threads[2];

        /* INSTANTIATE BROKER */
        broker *bounded_buffer = new broker;

        bounded_buffer->to_string();
        printf("\n");

        for(int i = 0; i < 2; i++){
            // int* a = (int*)malloc(sizeof(int));
            // *a = i+1;
            pthread_create(&threads[i], NULL, &produce, bounded_buffer);
        }
        for(int i = 0; i < 2; i++)
            pthread_join(threads[i], NULL);
        
        /* FREE SEMAPHORE MEMORY */
        sem_destroy(&mutex);

    } catch ( const exception& e ) {
        cerr << "ERROR: " << e.what() << endl;
    } catch (...) {
        cout << "Exception occurred";
    }
}