#include <stdlib.h>
#include "dynamicarray.h"

DynamicArray::DynamicArray(size_t initialCapacity) {
    _items = new int[initialCapacity];
    _capacity = initialCapacity;
}

DynamicArray::~DynamicArray() {
    delete[] _items;
}

float DynamicArray::get(int index) {
    if (index < _capacity && index > -1 )
        return _items[index];
    else 
        return -1;
}

void DynamicArray::set(int index, int value) {
    if (index < _capacity && index > -1)
        _items[index] = value;
}

size_t DynamicArray::size() {
    return _capacity;
}

void DynamicArray::resize(size_t newCapacity) {
    int *newArr = new int[newCapacity];
    for (int i = 0; i < fmin(_capacity, newCapacity); i++)
        newArr[i] = _items[i];

    _capacity = newCapacity;
    delete[] _items;
    _items = newArr;
}
