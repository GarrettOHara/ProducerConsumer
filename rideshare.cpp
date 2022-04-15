/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | April 2022
 **/

#include <vector>
#include <iostream>
#include <pthread.h>
#include <stdexcept>
#include <mutex>

#include "consumer.h"
#include "producer.h"

using namespace std;

int main(int arc, char **argv){
    try{
        /* INSTANTIATE THREADS */
        pthread_t producerA, producerB;



    } catch ( const exception& e ) {
        cerr << "ERROR: " << e.what() << endl;
    } catch (...) {
        cout << "Exception occurred";
    }
}