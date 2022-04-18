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
    this->current_size = 0;
    this->current_human_reqs = 0;
}

/* DECONSTUCTOR */
broker::~broker(){
    while(this->buffer.size()>0)
        this->buffer.pop();
}

/**
 * @brief offer
 *  - insert value into the bounded buffer
 * 
 * @param val 
 *  - request value
 */
bool broker::offer(bool human){
    /* OFFER HUMAN REQUEST */
    if(human){
        if(this->current_size <= this->get_max_size() &&
           this->current_human_reqs <= this->get_max_humans()){
            
            /* UPDATE COUNTS AND ADD TO BUFFER */
            this->current_size++;
            this->current_human_reqs++;
            this->buffer.push(human);            
        } else 
            return false;
    /* OFFER AUTONOMOUS REQUEST */
    } else {
        if(this->current_size <= this->get_max_size()){
            
            /* UPDATE COUNTS AND ADD TO BUFFER */
            this->current_size++;
            this->buffer.push(human);
        } else 
            return false;
    }
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
bool broker::poll(){
    if(this->current_size>0){
        bool tmp = this->buffer.front();
        if(tmp)
            this->current_human_reqs--;
        this->current_size--;
        this->buffer.pop();
    } else 
        return false;
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