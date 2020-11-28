#pragma once
#include "dynamicarray.h"


class Stack
{
   DynamicArray _array;
   size_t _size; 

public:
    explicit Stack(size_t size = 0);
    ~Stack();

    size_t size();

    void push(int value); 
    int peek(); 
    int pop();

    bool empty();

    void print();
    bool sorted();
};

