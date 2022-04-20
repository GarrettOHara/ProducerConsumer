/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | April 2022
 **/
#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#include <semaphore.h>

struct arguments{
   
    int   request_limit = 120;                  // program request limit

    int   human_driver_req = 0;                 // human driver request latency
    int   auton_driver_req = 0;                 // autonomous driver request latency

    int   cost_saving_consumer  = 0;            // const saving algorithm latency
    int   fast_match_consumer   = 0;            // fast matching algorithm latency

};

namespace args {
    void proccess_args(int argc,                // process user CLI arguments
        char **argv,                            // and set in arguments struct
        struct arguments *DATA);

    void print_args(struct arguments *DATA);    // to string method to print 
                                                // passed arguments
};

#endif