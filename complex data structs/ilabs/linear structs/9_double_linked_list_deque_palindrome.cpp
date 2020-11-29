#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class Deque
{
   struct Node * first_node;
   struct Node * last_node;
   size_t size_; 

   struct Node * node_create(int value);

public:
   Deque();
   ~Deque();
   size_t size();

   void push_back(int value);
   int pop_back();
   void push_front(int value);
   int pop_front();

   bool empty();

   void print();
   void insertOfNumber(long number);
   void clear();
};

struct Node 
{
    int data;
    struct Node * next;
    struct Node * prev;
};

bool isPalindrome(Deque & deq);
void makePalindrome(Deque & deq, long number);

//privat
long int correctEnter();

int main()
{
    Deque deq;

    long int number = correctEnter();
    // number = 2003;
    deq.insertOfNumber(number);

    deq.print();

    if (isPalindrome(deq)) cout << "Palindrome!" << endl;
    else 
    {
        makePalindrome(deq, number);
        cout << "\n--------------------------------\nCreated: palindrome" << endl;
        deq.print();
    }
}

void makePalindrome(Deque & deq, long number)
{
    deq.insertOfNumber(number);
    number = (number - (number % 10)) / 10;
    while(number)
    {
        deq.push_back(number % 10);
        deq.print();
        number = (number - (number % 10)) / 10;
    }
}


bool isPalindrome(Deque & deq)
{
    while(!deq.empty())
    {
        if (deq.size() == 1)
        {
            deq.pop_back();
            return true;
        }
        if (deq.pop_front() != deq.pop_back()) 
        {
            deq.clear();
            return false;
        }
    }
    return true;
}

void Deque::insertOfNumber(long number)
{
    if (size_ == 0)
    {
        while(number)
        {
            push_front(number % 10);
            print();
            number = (number - (number % 10)) / 10;
        }
    }
}

Deque::Deque()
{
    size_ = 0;
    first_node = nullptr;
    last_node = nullptr;
}

struct Node * Deque::node_create(int value)
{
    struct Node * new_node = new struct Node;
    new_node->data = value;
    new_node->next = nullptr;
    new_node->prev = nullptr;
    return new_node;
}

Deque::~Deque()
{
    clear();
}

void Deque::push_back(int value)
{
    struct Node * new_node = node_create(value);
    if (size_ == 0) 
    {
        first_node = new_node;
        last_node = new_node;
    }
    else 
    {
        last_node->next = new_node;
        new_node->prev = last_node;
        last_node = new_node;
    }
    size_++;
}

int Deque::pop_back()
{
    if (size_ != 0)
    {
        if (size_ > 1)
        {
            struct Node * new_last_node = last_node->prev;
            int buf = last_node->data;
            delete last_node;
            new_last_node->next = nullptr;
            last_node = new_last_node;
            size_--;
            return buf;
        }
        else 
        {
           int buf = last_node->data;
           delete last_node;
           first_node = nullptr;
           last_node = nullptr;
           size_--;
           return buf; 
        }
    }
    else return -1;
}

void Deque::push_front(int value)
{
    struct Node * new_node = node_create(value);
    if (size_ == 0) 
    {
        first_node = new_node;
        last_node = new_node;
    }
    else 
    {
        first_node->prev = new_node;
        new_node->next = first_node;
        first_node = new_node;
    }
    size_++;
}

int Deque::pop_front()
{
    if (size_ != 0)
    {
        if (size_ > 1)
        {
            struct Node * new_first_node = first_node->next;
            int buf = first_node->data;
            delete first_node;
            new_first_node->prev = nullptr;
            first_node = new_first_node;
            size_--;
            return buf;
        }
        else 
        {
           int buf = first_node->data;
           delete first_node;
           first_node = nullptr;
           last_node = nullptr;
           size_--;
           return buf; 
        }
    }
    else return -1;
}

size_t Deque::size()
{
    return size_;
}

bool Deque::empty()
{
    if (size_ == 0) return true;
    else return false;
}

void Deque::clear()
{
    struct Node * node = first_node;
    while (node != nullptr)
    {
        struct Node * next = node->next;
        delete node;
        node = next;
    }
    size_ = 0;
}

void Deque::print()
{
    struct Node * node = first_node;
    if (node != nullptr)
    { 
        printf("Deque: ");
        while (node != nullptr)
        {
            printf("[%i] ", node->data);
            node = node->next;
        }
        cout << endl;
    }
    else printf("NULL\n");
}

//privat 

long correctEnter()
{
    long value = 0;
    cout << "Enter value" << endl;
    long check = scanf("%ld", &value);
    if ((check == 0) || (value < 1) || log10(value) + 1 > 19)
    {
        printf("Please enter int numbers > 0 and < 10^19\n");
        exit(1);
    }
    else return value;
}