/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | April 2022
 **/
#ifndef SHARED_DATA_H_
#define SHARED_DATA_H_

#include <semaphore.h>

#include "broker.h"

typedef struct shared_data{
    sem_t   *mutex;    
    broker  *buffer;
    int     sleep_time;
    
    int   request_limit         = 120;
    int   current_requests      = 0;

    int   human_driver_req      = 0;
    int   auton_driver_req      = 0;

    int   cost_saving_consumer  = 0;
    int   fast_match_consumer   = 0;

}SHARED_DATA;

// typedef struct args {
//     int   human_driver_req     = 0;
//     int   auton_driver_req     = 0;

//     int   cost_saving_consumer = 0;
//     int   fast_match_consumer  = 0;
// };

#endif