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

/* CONSTUCTOR */
broker::broker(){
    this->total_requests = 0;
    this->current_requests = 0;
    this->current_human_reqs = 0;
    
    // int a[] = {0,0};
    // int b[] = {0,0};
    // this->consumed[0] = a;
    // this->consumed[1] = b;

    std::vector<int> a = {0,0}; 
    std::vector<int> b = {0,0};

    this->consumed.push_back(a);
    this->consumed.push_back(b);
}

/* DECONSTUCTOR */
broker::~broker(){
    while(this->buffer.size()>0)
        this->buffer.pop();
}

/**
 * @brief offer
 *  - insert request into the bounded buffer
 * 
 * @param val 
 *  - request value
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
 * @brief poll
 *  - remove first request from queue
 * 
 * @param index 
 *  - index of request
 * @param val 
 *  - value of request
 */
bool* broker::poll(){
    bool *arr = new bool[2];
    if(this->current_requests>0){
        bool tmp = this->buffer.front();
        if(tmp){
            this->current_human_reqs--;
            this->consumed_human_reqs++;
        }
        this->current_requests--;
        this->consumed_requests++;
        this->buffer.pop();
        arr[0]=true;
        arr[1]=tmp;
        return arr;
    } else 
        return arr;
}

/**
 * @brief to_string
 *  - print data of buffer to std out
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
 * @brief get_max_size
 *  - return max size of bounded buffer
 * 
 * @return int 
 */
int broker::get_max_size(){ return this->max_size; }

/**
 * @brief get_max_humans
 *  - return max size of humans requests
 * 
 * @return int 
 */
int broker::get_max_humans(){ return this->max_humans; }