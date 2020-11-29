#include "hashmap.h"
#include <iostream>
using namespace std;

HashTable::HashTable(int size) {
    _loadness = 0;
    _size = size;
    _table = new Value[size + 1];
}

HashTable::~HashTable() {
    delete[] _table;
}

void HashTable::insertEntry(Key &key, Value &value) {
    if ((double)_loadness / (double)_size >= 0.8)
        _keys = rehashing();
    
    int x = getHash1(key);
    int y = getHash2(key);
    for (int i = 0; i < _size; i++) {
        if (_table[x].averageGrade == -1) {//if null or deleted 
            _table[x] = value;
            _keys[x] = key;
            _loadness++;
            cout << "Insertion successful!" << endl;
            return;
        }
        else if (_keys[x] == key) {
            _table[x] = value;
        }
        x = (x + i * y) % _size;
    }

    cout << "Unexpected insertion error" << endl;
    exit(1);
}

void HashTable::removeEntry(Key &key) {
    int x = getHash1(key);
    int y = getHash2(key);

    for (int i = 0; i < _size; i++) {
        if (_keys[x] == key) {
            _keys.erase(x);
            _table[x].address = "";
            _table[x].averageGrade = -1;
            _table[x].birthDate = "";
            _table[x].disciplines.d.clear();
            _table[x].yearOfEntry = -1;
            _loadness--;
            cout << "Removal successful!" << endl;
            return;
        }
        x = (x + i * y) % _size;
    }
    cout << "Student not found." << endl;
}

Value HashTable::findEntry(Key key) {
    int x = getHash1(key);
    int y = getHash2(key);

    for (int i = 0; i < _size; i++) {
        if (_keys[x] == key) {
            return _table[x];
        }
        x = (x + i * y) % _size;
    }
    
    cout << "Student not found." << endl;
    return {"", "", -1, list<Discipline>(), -1};
}

map<int, Key> HashTable::rehashing() {
    cout << "Rehashing!" <<  endl;
    Value *newTable = new Value[_size * 2];
    map<int, Key> newKeys;
    _loadness = 0;
    for (int j = 0; j < _size; j++) {
        for (int i = 0; i < _size - 1; i++) {
            int index = (getHash1(_keys[j]) + i * getHash2(_keys[j])) % _size;
            if (newTable[index].averageGrade == -1) {
                newTable[index] = _table[j];
                newKeys.insert(pair<int, Key>(index, _keys[j]));
                _loadness++;
            }
        }
    }
    _size *= 2;
    delete[] _table;
    _table = newTable;
    return newKeys;
}

long HashTable::hashCode(Key key) {
    long code;
    string hash = key.firstName + key.lastName + to_string(key.studentID);
    for (int i = 0; i < hash.length(); i++) 
        code += (int)hash[i] * (1 + i);
    return code;
}

int HashTable::getHash1(Key key) {
    return hashCode(key) % _size;
}

int HashTable::getHash2(Key key) {
    return hashCode(key) % (_size - 1) + 1;
}

void updateDisciplinesList(Value &v, const Discipline &disciplineName, bool status){
    if (status) { //add 
        if (find(v.disciplines.d.begin(), v.disciplines.d.end(), disciplineName) == v.disciplines.d.end()) { //not found
            v.disciplines.d.push_back(disciplineName);
            v.averageGrade = calcAverageGrade(v.disciplines);
        }
        else 
            cout << endl << "Discipline already exists." << endl;
        return;
    }
    else if (!status) { //delete
        if (find(v.disciplines.d.begin(), v.disciplines.d.end(), disciplineName) != v.disciplines.d.end()) { //found
            v.disciplines.d.remove(disciplineName);
            v.averageGrade = calcAverageGrade(v.disciplines);
        }
        else 
            cout << endl << "Discipline does not exist." << endl;
        return;
    }
    cout << "Unexpected update error" << endl;
    exit(1);
}

struct Discipline findDiscipline(string name, const DisciplinesList &disciplines) {
    for (const auto &item : disciplines.d)
        if (item.disciplineName == name) {
            cout << "Discipline found!" << endl;
            return item;
        }
    cout << "Discipline not found." << endl;
    return {string(), -1};
}

void printDisciplines(const DisciplinesList &disciplines) {
    for (const auto &item : disciplines.d)
        cout << item.disciplineName << " | " << item.grade << endl;
}

double calcAverageGrade(const DisciplinesList &disciplines) {
    double sum = 0;
    for (auto item : disciplines.d) 
        sum += item.grade;
    return sum / disciplines.d.size(); 
}

void HashTable::print() {
    cout << _loadness << " / " << _size << endl; 
    for (int i = 0; i < _size; i++) {
        if (_table[i].averageGrade == -1)
            cout << "[" << i << "] DELETED" << endl;
        else 
            cout << "[" << i << "] " << _keys[i].firstName << " " << _keys[i].lastName << " | " << _keys[i].studentID << endl;
    }
}

int getch() {
    int ch;
    struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

void show(int pos) {
    if (pos == 0)
        cout << "-> ADD new key\nDELETE key\nFIND key\nPRINT table" << endl;
    if (pos == 1)
        cout << "ADD new key\n-> DELETE key\nFIND key\nPRINT table" << endl;
    if (pos == 2)
        cout << "ADD new key\nDELETE key\n-> FIND key\nPRINT table" << endl;
    if (pos == 3)
        cout << "ADD new key\nDELETE key\nFIND key\n-> PRINT table" << endl;
}