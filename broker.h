/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | April 2022
 **/
#ifndef BROKER_H_
#define BROKER_H_

#include <queue>
#include <iostream>

#include "request.h"

#define MAX_SIZE   12
#define MAX_HUMANS 4

class broker{
    private:
        int max_size   = MAX_SIZE;              // maxumum number of requests in buffer
        int max_humans = MAX_HUMANS;            // maximum number of human driver requests

    public:
        broker();                               // constructor

        std::queue<struct request> buffer;
};

#endif