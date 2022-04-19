#include <cstring>
#include <iostream>
#include "arguments.h"

using namespace std;

void args::proccess_args(int argc, char **argv, struct arguments *DATA){
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i],"-n")==0){
            int val = atoi(argv[i+1]);
            DATA->request_limit = val;
            i++;
            continue;
        } else if(strcmp(argv[i],"-c")==0){
            int val = atoi(argv[i+1]);
            DATA->cost_saving_consumer = val;
            i++;
            continue;
        } else if(strcmp(argv[i],"-f")==0){
            int val = atoi(argv[i+1]);
            DATA->fast_match_consumer = val;
            i++;
            continue;
        }else if(strcmp(argv[i], "-h")==0){
            int val = atoi(argv[i+1]);
            DATA->human_driver_req = val;
            i++;
            continue;
        }else if(strcmp(argv[i], "-a")==0){
            int val = atoi(argv[i+1]);
            DATA->auton_driver_req = val;
            i++;
            continue;
        }
    }
}

void args::print_args(struct arguments *DATA){
    cout << DATA->request_limit << "\n"
         << DATA->human_driver_req << "\n"
         << DATA->auton_driver_req << "\n"
         << DATA->cost_saving_consumer << "\n"
         << DATA->fast_match_consumer 
         << endl;
}