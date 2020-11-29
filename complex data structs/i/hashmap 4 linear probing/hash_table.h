#pragma once 

#include <math.h>
#include <optional>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Key
{
    string username;
    string password;
};

struct Value
{
    string emailAddress = "NULL";
    int age = 0;
};

struct Entiti
{

    Key key;
    Value value;
};


class HashTable
{
    int loadness;
    int size;
    Entiti * table;
    vector<string> * ageTable;

    long hashCode(Key & key_);                        //обчислює хеш-код ключа. Для обчислення хеш-коду кожного  поля ключа за  необхідності пишуться  додаткові  функції hashCodeString

public:
    void insertEntry(Entiti & entiti);    //додає нову пару <key,value> у хеш-таблицю. Якщо така пара вже існує у хеш-таблиці, виконується оновлення значення value за ключем key. Вирішення колізії відбувається відповідно до варіанту
    bool removeEntry(Key & key_);                    //видаляє пару <key,value> з хеш-таблиці за ключем key. Для методів відкритої адресації позначає відповідний слот маркером DELETED.
    optional<Value> findEntry(Key & key_);                     //виконує пошук даних у хеш-таблиці за ключем key.
    void rehashing();                                //виконує  перехешування  хеш-таблиці,  коли  досягається  відповідне значення фактору завантаженості.
    int getHash(Key & key_);                        //обчислює функцію хешування для визначення індексу слота хеш-таблиці, у який має відобразитись ключ key


    void print(int status);

    explicit HashTable(int size_ = 1);
    ~HashTable();

    int getLoadness();
    void addAge(string username, int newAge);
    vector<string> getAgeGroup(int index);
};