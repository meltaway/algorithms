#pragma once
#include <stdlib.h>
#include <cmath>
#include <iostream>
using namespace std;

class DynamicArray 
{
    int * _items;
    size_t _capacity;

public:
    DynamicArray(size_t size);
    ~DynamicArray();

    float get(int index);
    void set(int index, int value);
    
    size_t size();
    void resize(size_t newSize);
};