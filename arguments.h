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
   
    int   request_limit         = 120;

    int   human_driver_req      = 0;
    int   auton_driver_req      = 0;

    int   cost_saving_consumer  = 0;
    int   fast_match_consumer   = 0;

};

namespace args {
    void proccess_args(int argc, char **argv, struct arguments *DATA);
    void print_args(struct arguments *DATA);
};

#endif