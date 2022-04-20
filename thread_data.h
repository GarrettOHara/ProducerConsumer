/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | April 2022
 **/
#ifndef THREAD_DATA_H_
#define THREAD_DATA_H_

#include <semaphore.h>

#include "broker.h"
#include "arguments.h"

struct threading_data {
    broker *buffer;         // pointer to the broker object
    sem_t  *mutex;          // pointer to binary semaphore
    sem_t  *human_req;      // pointer to human_req thread semaphore
    sem_t  *robot_req;      // pointer to robot_req thread semaphore
    sem_t  *cost_algo;      // pointer to cost_algo thread semaphore
    sem_t  *fast_algo;      // pointer to fast_algo thread semaphore
    struct arguments *args; // pointer to CLI arguments struct
    int latency = 0;        // latency of process
    int id;                 // id for io functions
};

#endif