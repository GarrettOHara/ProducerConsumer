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
    // char    *request_type;

}SHARED_DATA;

#endif