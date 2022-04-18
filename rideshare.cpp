/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | April 2022
 **/
#include <cstring>

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

#define SEMAPHORE_RESOURCES 1

using namespace std;

void print_args(struct shared_data *DATA){
    cout << DATA->request_limit << "\n"
         << DATA->current_requests << "\n"
         << DATA->human_driver_req << "\n"
         << DATA->auton_driver_req << "\n"
         << DATA->cost_saving_consumer << "\n"
         << DATA->fast_match_consumer 
         << endl;
}

void proccess_args(int argc, char **argv, struct shared_data *DATA){
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i],"-n")==0){
            int val = atoi(argv[i+1]);
            DATA->request_limit = val;
            cout << "ENTER: " << val << endl;
            i++;
            continue;
        } else if(strcmp(argv[i],"-c")==0){
            int val = atoi(argv[i+1]);
            DATA->cost_saving_consumer = val;
            i++;
            continue;
        } else if(strcmp(argv[i],"-f")==0){
            int val = atoi(argv[i+1]);
            DATA->fast_match_consumer = val;
            i++;
            continue;
        }else if(strcmp(argv[i], "-h")==0){
            int val = atoi(argv[i+1]);
            DATA->human_driver_req = val;
            i++;
            continue;
        }else if(strcmp(argv[i], "-a")==0){
            int val = atoi(argv[i+1]);
            DATA->auton_driver_req = val;
            i++;
            continue;
        }
    }
    // int arr[2];
    // DATA.request_type = &arr;
    // DATA.request_type[0] = DATA.human_driver_req;
    // DATA.request_type[1] = DATA.auton_driver_req;
}

int main(int arc, char **argv){
    try{

        sem_t mutex;

        /* INSTANTIATE SHARED DATA STRUCTURE */
        struct shared_data DATA;
        proccess_args(arc, argv, &DATA);
        print_args(&DATA);

        /* INSTANTIATE BINARY SEMAPHORE */
        sem_init(&mutex, 0, SEMAPHORE_RESOURCES);
        
        /* INSTANTIATE THREADS */
        pthread_t producerA, producerB, consumerA, consumerB;

        /* INSTANTIATE BROKER */
        broker *bounded_buffer = new broker;

        /* SET SHARED DATA POINTERS */
        DATA.mutex  = &mutex;
        DATA.buffer = bounded_buffer;


        /* CREATE PRODUCER CONSUMER THREADS WITH RESPECTIVE PROCESS LATENCY*/
        DATA.sleep_time = DATA.human_driver_req;
        pthread_create(&producerA,NULL,producer::produce,&DATA);

        DATA.sleep_time = DATA.auton_driver_req;
        // pthread_create(&producerB,NULL,producer::produce,&DATA);

        DATA.sleep_time = DATA.fast_match_consumer;
        pthread_create(&consumerA,NULL,consumer::consume,&DATA);

        DATA.sleep_time = DATA.cost_saving_consumer;
        pthread_create(&consumerB,NULL,consumer::consume,&DATA);
        
        /* WAIT FOR ALL THREAD PROCESSES TO FINISH */
        pthread_join(producerA,NULL);
        // pthread_join(producerB,NULL);
        pthread_join(consumerA,NULL);
        pthread_join(consumerB,NULL);
        
        /* FREE SEMAPHORE MEMORY */
        sem_destroy(&mutex);

    } catch ( const exception& e ) {
        cerr << "ERROR: " << e.what() << endl;
    } catch (...) {
        cout << "Exception occurred";
    }
}