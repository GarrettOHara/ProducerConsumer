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

#include "request_obj.h"

#define MAX_SIZE   12
#define MAX_HUMANS 4

class broker{
    private:
        int max_size   = MAX_SIZE;              // maxumum number of requests in buffer
        int max_humans = MAX_HUMANS;            // maximum number of human driver requests

    public:
        broker();                               // constructor
        ~broker();                              // deconstructor

        std::queue <int> buffer;                // replace with request obj
        // std::vector<int> ledger;                // replace with request obj
        int current_size;                       // current size in bounded buffer
        int current_human_reqs;

        void offer(int val);                    // insert request into broker (use tmp int val)
        void poll();        //return request that was popped 

        void to_string();                       // to string method: prints buffer data
        int get_max_size();                     // get max buffer size
        int get_max_humans();                   // get max human size
};

#endif