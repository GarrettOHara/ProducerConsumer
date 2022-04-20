/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | April 2022
 **/
#include <vector>
#include <iostream>

#include "broker.h"

#define INSERT_SUCCESS_INDX 0
#define HUMAN_REQUEST_INDX  1

/**
 * @brief Construct a new broker::broker object
 * 
 */
broker::broker(){
    this->total_requests = 0;
    this->current_requests = 0;
    this->current_human_reqs = 0;

    std::vector<int> a = {0,0}; 
    std::vector<int> b = {0,0};

    this->consumed.push_back(a);
    this->consumed.push_back(b);
}

/**
 * @brief Destroy the broker::broker object
 * 
 */
broker::~broker(){
    while(this->buffer.size()>0)
        this->buffer.pop();
}

/**
 * @brief insert request into the bounded buffer
 * 
 * @param val request type
 *  - true:  human
 *  - false: robot
 */
bool broker::offer(bool human){
    /* OFFER HUMAN REQUEST */
    if(human){
        if(this->current_requests < this->get_max_size() &&
           this->current_human_reqs < this->get_max_humans()){
            
            /* UPDATE COUNTS AND ADD TO BUFFER */
            this->current_requests++;
            this->current_human_reqs++;
            this->total_human_reqs++;
            this->buffer.push(human);
        } else 
            return false;
    
    /* OFFER AUTONOMOUS REQUEST */
    } else {
        if(this->current_requests < this->get_max_size()){
            
            /* UPDATE COUNTS AND ADD TO BUFFER */
            this->current_requests++;
            this->buffer.push(human);
        } else 
            return false;
    }
    this->total_requests++;
    return true;
}

/**
 * @brief retrive request at the 
 * head of the queue
 * 
 * @return arr
 *  - arr[0]: retrived value
 *  - arr[1]: request type
 *      - true:  human
 *      - false: robot
 */
bool* broker::poll(){
    /* INITALIZE POINTER ARRAY
        TO STORE RETURN VALUES */
    bool *arr = new bool[2];

    /* CHECK IF THE QUEUE IS EMPTY */
    if(this->current_requests>0){

        /* STORE REQUEST VALUE */
        bool tmp = this->buffer.front();

        /* IF REQUEST IS TRUE: HUMAN */
        if(tmp){
            this->current_human_reqs--;
            this->consumed_human_reqs++;
        }
        /* UPDATE BUFFER DATA */
        this->current_requests--;
        this->consumed_requests++;
        this->buffer.pop();

        /* RETRIVAL SUCCESS, RETURN REQUEST TYPE*/
        arr[INSERT_SUCCESS_INDX]=true;
        arr[HUMAN_REQUEST_INDX]=tmp;
        return arr;
    } else
        /* DID NOT RETRIEVE VALUE */
        return arr;
}

/**
 * @brief print contents of buffer
 * 
 */
void broker::to_string(){
    std::vector<int> memory;
    while(this->buffer.size()>0){
        memory.push_back(this->buffer.front());
        this->buffer.pop();
    }
    for(int i = 0; i < memory.size(); i++)
        printf("%d ", memory.at(i));
    printf("\n");

    for(auto val : memory)
        this->buffer.push(val);
}

/**
 * @brief return max size of bounded buffer
 * 
 * @return int
 */
int broker::get_max_size(){ return this->max_size; }

/**
 * @brief return max size of humans requests
 * 
 * @return int
 */
int broker::get_max_humans(){ return this->max_humans; }