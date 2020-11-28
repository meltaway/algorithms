#include "stack.h"


Stack::Stack(size_t size) : _array{size}, _size{0} {
}

Stack::~Stack() {
    _size = 0;
}

size_t Stack::size() {
    return _size;
}

void Stack::push(int value) {
    _array.set(_size, value);
    _size++;
}

int Stack::peek() {
    if (_size != 0) 
        return _array.get(_size - 1);
    else return -1;
}

int Stack::pop() {
    if (_size > 0) 
    {
        _size--;
        return _array.get(_size);
    }
    else return -1;
}

bool Stack::empty() {
    if (_size == 0) return true;
    else return false;
}

void Stack::print() {
    for (int i = 0; i < _size ; i++)
        cout << _array.get(i) << "---";
    cout << endl;
}

bool Stack::sorted() {
    for (int i = 0; i < _array.size() - 1; i++)
        if (_array.get(i) < _array.get(i + 1))
            return false;
    return true;
}