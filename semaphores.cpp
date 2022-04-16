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

// #include "io.h"
// #include "consumer.h"
// #include "producer.h"
// #include "ridesharing.h"

#define PRODUCER "producer"
#define CONSUMER "consumer"

using namespace std;

sem_t mutex;

void* sample(void* args){
    sem_wait(&mutex);
    sleep(1);
    printf("Hello from %d\n", *(int*)args);
    sem_post(&mutex);
    // free(args);
    return NULL;
}

int main(int arc, char **argv){
    try{
        /* INSTANTIATE THREADS */
        pthread_t producerA, producerB;

        sem_init(&mutex, 0, 1);

        pthread_t threads[2];

        for(int i = 0; i < 2; i++){
            int* a = (int*)malloc(sizeof(int));
            *a = i;
            pthread_create(&threads[i], NULL, &sample, a);
        }

        for(int i = 0; i < 2; i++){
            pthread_join(threads[i], NULL);
        }


        // int* a = (int*)malloc(sizeof(int));
        // *a = 1;
        // pthread_create(&producerA, NULL, &sample, a);
        // int* b = (int*)malloc(sizeof(int));
        // *b = 2;
        // pthread_create(&producerB, NULL, &sample, b);

        // pthread_join(producerA,NULL);
        // pthread_join(producerB,NULL);

        // FREE SEMAPHORE MEMORY
        sem_destroy(&mutex);

    } catch ( const exception& e ) {
        cerr << "ERROR: " << e.what() << endl;
    } catch (...) {
        cout << "Exception occurred";
    }
}