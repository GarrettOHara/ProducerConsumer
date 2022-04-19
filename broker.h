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

#define MAX_SIZE   12
#define MAX_HUMANS 4
#define ALGO_COUNT 2

using namespace std;

class broker{
    private:
        int max_size   = MAX_SIZE;              // maxumum number of requests in buffer
        int max_humans = MAX_HUMANS;            // maximum number of human driver requests

    public:
        broker();                               // constructor
        ~broker();                              // deconstructor

        queue <bool> buffer;                    // replace with request obj

        vector<vector<int> > consumed;          // vector[ALGORITHM][REQUEST TYPE] keep track of 
                                                // all consumed requests counts
        
        int total_requests;                     // keep track of total requests sent to broker
        int total_human_reqs;                   // keep track of total human requests sent to broker

        int consumed_requests;                  // total consumed requests
        int consumed_human_reqs;                // total consumed human requests

        int current_requests;                   // current requests in bounded buffer
        int current_human_reqs;                 // current human requests in bounded buffer

        bool offer(bool human);                 // insert request into bounded buffer
        bool* poll();                           // remove request from bounded buffer

        void to_string();                       // to string method: prints buffer data
        int get_max_size();                     // get max buffer size
        int get_max_humans();                   // get max human size
};

#endif