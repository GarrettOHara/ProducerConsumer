/**
 * This Program was written by:
 * 
 * Garrett O'Hara cssc1136 RedId: 822936303
 * 
 * CS 480 | Professor Shen | April 2022
 **/
#include <iostream>

#include "broker.h"

/* CONSTUCTOR */
broker::broker(){
    for(int i = 0; i < broker::get_max_size(); i++){
        broker::ledger.push_back(0);
    }
}

/* DECONSTUCTOR */
broker::~broker(){ }

void broker::offer(int val){
    broker::ledger.at(val) = val;
}

void broker::poll(int index, int val){
    if(index > get_max_size)
        printf("OUT OF BOUNDS");
    else
        broker::ledger.emplace(ledger.begin()+index,val);
}

void broker::to_string(){
    int size = broker::get_max_size();
    for(int i = 0; i < size; i++)
        printf("%d ", broker::ledger.at(i));
}

int broker::get_max_size(){ return this->max_size; }
int broker::get_max_humans(){ return this->max_humans; }