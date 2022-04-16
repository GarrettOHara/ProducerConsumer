#include <iostream>

#include "broker.h"

/* CONSTUCTOR */
broker::broker(){
    for(int i = 0; i < broker::max_size; i++){
        broker::ledger.push_back(0);
    }
}

/* DECONSTUCTOR */
broker::~broker(){ }

void broker::offer(int val){
    broker::ledger.at(val) = val;
}

void broker::to_string(){
    int size = broker::buffer.size();
    for(int i = 0; i < size; i++)
        printf("%d ", broker::ledger.at(i));
}