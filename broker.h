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
#include <vector>
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
        ~broker();

        // std::queue <struct requests> buffer;
        std::vector<int> ledger; // <struct request>

        void offer(int val);                    // insert request into broker (use tmp int val)
        void poll();

        void to_string();                       // to string method: prints buffer data
        int get_max_size();
        int get_max_humans();
};

#endif