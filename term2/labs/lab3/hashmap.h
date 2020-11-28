#pragma once
#include <iostream>
#include <list>
#include <map>
#include <algorithm>
#include <termios.h>
#define STDIN_FILENO 0
using namespace std;

struct Discipline {
    string disciplineName;
    int grade = -1;

    bool operator==(const Discipline &rhs) {
        return this->disciplineName == rhs.disciplineName;
    }
};

struct DisciplinesList {
    list<Discipline> d;
};

struct Key {
    string firstName;
    string lastName;
    int studentID;

    bool operator== (const Key &rhs) {
        return this->firstName == rhs.firstName && this->lastName == rhs.lastName && this->studentID == rhs.studentID;
    }
};

struct Value {
    string birthDate = "";
    string address = "";
    int yearOfEntry = -1;
    DisciplinesList disciplines;
    double averageGrade = -1;
};

class HashTable {
    Value *_table;
    int _loadness;
    int _size;
    map<int, Key> _keys;

    long hashCode(Key key);
    map<int, Key> rehashing();
    int getHash1(Key key);
    int getHash2(Key key);

public:
    HashTable(int size);
    ~HashTable();
    void insertEntry(Key &key, Value &value);
    void removeEntry(Key &key);
    Value findEntry(Key key);
    void print();
};

void updateDisciplinesList(Value &v, const Discipline &disciplineName, bool status);
struct Discipline findDiscipline(string name, const DisciplinesList &disciplines);
void printDisciplines(const DisciplinesList &disciplines);
double calcAverageGrade(const DisciplinesList &disciplines);
int getch();
void show(int pos);