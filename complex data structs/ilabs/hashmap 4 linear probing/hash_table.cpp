#include "hash_table.h"
#include <math.h>

long HashTable::hashCode(Key & key_)
{
    long  hash = 0;
    string hashable = key_.password + key_.username;
    for (int i = 0; i < hashable.length(); i++)
    {
        hash += hashable[i] * (i + 1) * 94;
    }
    return hash;
}

int HashTable::getHash(Key & key_)
{
    return hashCode(key_) % size;
}


HashTable::HashTable(int size_)
{
    loadness = 0;
    size = size_;
    table = new Entiti[size];
    ageTable = new vector<string>[4];
}

HashTable::~HashTable()
{
    delete[] table;
    delete[] ageTable;
}
       
    
void HashTable::insertEntry(Entiti & entiti)
{
    int hash_index = getHash(entiti.key);

    if (loadness == size - 1) rehashing();

    for(int i = hash_index ;; i++)
    {
        if( table[i].key.password == entiti.key.password && table[i].key.username == entiti.key.username)
        {
            table[i] = entiti;
            break;
        }
        if (((table[i].value.emailAddress == "NULL" || table[i].value.emailAddress == "DELETED") && table[i].value.age == 0))
        {
            table[i] = entiti;
            loadness++;
            break;
        } 
        if (i == size) i = 0;

    }
    addAge(entiti.key.username, entiti.value.age);
}

bool HashTable::removeEntry(Key & key_)   
{
    int check = 0;
    int index = getHash(key_);
    for(int i = index ;; i++)
    {
        if(table[i].key.password == key_.password && table[i].key.username == key_.username)
        {
            table[i].value.emailAddress = "DELETED";
            table[i].value.age = 0;
            loadness--;
            return true;
        }
        if (i == size) i = 0;
        if (i == index) check++;
        if (i == index && check == 2)
            return false;
    }

}

optional<Value> HashTable::findEntry(Key & key_)
{
    int index = getHash(key_);
    int check = 0;
    for(int i = index ;; i++)
    {
        if((table[i].key.password == key_.password) && (table[i].key.username == key_.username))
        {
            return optional<Value>{table[i].value};
        }
        if (i == index) check++;
        if (i == index && check == 2)
        {
            return nullopt;
        } 
        if (i == size) i = 0;
    }
}

void HashTable::rehashing()
{
    size_t old_size = size;
    size *=2;
    Entiti * newTable = new Entiti[size];
    loadness = 0;
    for (int j = 0; j < old_size; j++)
    {
        int hash_index = getHash(table[j].key);

        for(int i = hash_index ;; i++)
        {
            if( newTable[i].key.password == table[j].key.password && newTable[i].key.username == table[j].key.username)
            {
                newTable[i] = table[j];
                break;
            }
            if (((newTable[i].value.emailAddress == "NULL" || newTable[i].value.emailAddress == "DELETED") && newTable[i].value.age == 0))
            {
                newTable[i] = table[j];
                loadness++;
                break;
            } 
            if (i == size) i = 0;
        }
    }
    delete[] table;
    table = newTable;
}

void HashTable::print(int status)
{
    cout << "-----------" << endl;
    cout << "                                  loadness: " << loadness << " / " << "" << size << " " << endl;
    if (status == 0)
    {
        for(int i = 0; i < size; i++)
        {
            cout << "[" << i << "] " << table[i].value.emailAddress << "   " << table[i].value.age <<"   "<<  table[i].key.username << endl; 
        }
    }
    cout << "-----------" << endl;
}

void HashTable::addAge(string username, int newAge)
{
    //18-25, 26-35, 36-50,  50+.
    if (newAge >= 18 && newAge <=25)
    {
        ageTable[0].push_back(username);
    }
    if (newAge >= 26 && newAge <=35)
    {
        ageTable[1].push_back(username);
    }
    if (newAge >= 36 && newAge <=50)
    {
        ageTable[2].push_back(username);
    }
    if (newAge >= 50 )
    {
        ageTable[3].push_back(username);
    }
}

vector<string> HashTable::getAgeGroup(int index)
{
    return ageTable[index];
}

int HashTable::getLoadness()
{
    return loadness;
}