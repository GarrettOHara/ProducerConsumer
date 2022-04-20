/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | April 2022
 **/
#include <cstring>
#include <iostream>
#include <stdexcept> 

#include "arguments.h"

using namespace std;

/**
 * @brief reads CLI arguments and sets passed data
 *    to the program
 * 
 * @param argc count of arguments
 * @param argv pointer to arguments
 * @param DATA struct to hold argument data
 */
void args::proccess_args(int argc, char **argv, struct arguments *DATA){
    for(int i = 1; i < argc; i++){

        /* CAST ARGUMENT VALUE TO INTEGER */
        int val = atoi(argv[i+1]);

        /* CHECK INVALID BOUNDS */
        if(val < 0)
            throw std::invalid_argument("Argument must be greater than 0");
        
        /* PROCESS REQUEST COUNT ARGUMENT */
        if(strcmp(argv[i],"-n")==0 && i+1 < argc){
            DATA->request_limit = val;
            i++;
            
        /* PROCESS COST SAVING ALGORITHM LATENCY */
        } else if(strcmp(argv[i],"-c")==0 && i+1 < argc){
            DATA->cost_saving_consumer = val;
            i++;
            
        /* PROCESS FAST MATCHING ALGORITHM LATENCY */
        } else if(strcmp(argv[i],"-f")==0 && i+1 < argc){
            DATA->fast_match_consumer = val;
            i++;
            
        /* PROCESS HUMAN DRIVER REQUEST LATENCY */
        }else if(strcmp(argv[i], "-h")==0 && i+1 < argc){
            DATA->human_driver_req = val;
            i++;
            
        /* PROCESS AUTONOMOUS DRIVER REQUEST LATENCY */
        }else if(strcmp(argv[i], "-a")==0 && i+1 < argc){
            DATA->auton_driver_req = val;
            i++;
        }
    }
}

/**
 * @brief basic to string method for CLI args
 * 
 * @param DATA user arguments
 */
void args::print_args(struct arguments *DATA){
    cout << DATA->request_limit << "\n"
         << DATA->human_driver_req << "\n"
         << DATA->auton_driver_req << "\n"
         << DATA->cost_saving_consumer << "\n"
         << DATA->fast_match_consumer 
         << endl;
}