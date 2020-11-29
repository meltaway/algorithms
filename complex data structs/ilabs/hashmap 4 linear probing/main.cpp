#include <unistd.h>
#include <termios.h>
#include <time.h>
#include <iostream>
#include <string>

#include "hash_table.h"

using namespace std;


int getch();
void show(HashTable & table_);
void printOptions(int status);
void main_menu(HashTable & table_);
int correctEnter();
void remove_menu(HashTable & table_);
void insert_menu(HashTable & table_);
void find_menu(HashTable & table_);
void printMenu(HashTable & table_);
void load(HashTable & table_);

int main()
{
    srand(time(0));
    HashTable hs{5};
    show(hs);
}

int getch()
{
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

void identifyAgeCategories(HashTable & table)
{
     //18-25, 26-35, 36-50,  50+.
    if (table.getLoadness() != 0)
    {
        for (int i = 0; i < 4; i++)
        {
            vector<string> buf  = table.getAgeGroup(i);
            cout << (double) buf.size() / (double) table.getLoadness() * 100 << " % " << endl;
            if (i == 0) cout << "[18 - 25]: ";
            if (i == 1) cout << "[25 - 35]: ";
            if (i == 2) cout << "[36 - 50]: ";
            if (i == 3) cout << "[50+]: ";
            for (auto item : buf)
            {
                cout << item << " ";
            }
            cout << endl;
        }
    }
    else cout << "Table is empty" << endl;
    cout << endl <<"[Press Enter.......]" << endl;
    string buf_;
    getline(cin, buf_);
}

void show(HashTable & table_)
{
    main_menu(table_);
}

void printOptions(int status)
{
    if (status == 1) cout << "->";
    cout << "Insert user" << endl;
    if (status == 2) cout << "->";
    cout << "Find user" << endl;
    if (status == 3) cout << "->";
    cout << "Delete user" << endl;
    if (status == 4) cout << "->";
    cout << "Check all users" << endl;
    if (status == 5) cout << "->";
    cout << "Load users" << endl;
    if (status == 6) cout << "->";
    cout << "Identify age categories" << endl;
    if (status == 7) cout << "->";
    cout << "[EXIT]" << endl;
}


void main_menu(HashTable & table_)
{
    int status = 1;
    int loadStatus = 0;
    char key = 0;
    while (1)
    {
        system("clear");
        printOptions(status);
        table_.print(10);
        key = getch();
        if (key == 'w')
        {
            if (status > 1) status--;
        }
        if (key == 's')
        {
            if(status < 7) status++;
        }
        if (key == '\n')
        {
            if (status == 1)
            {
                insert_menu(table_);
            }
            if (status == 2)
            {
                find_menu(table_);
            }
            if (status == 3)
            {
                remove_menu(table_);
            }
            if (status == 4)
            {
                printMenu(table_);
            }
            if (status == 5)
            {
                if (loadStatus == 0) load(table_);
                else 
                {
                    cout << "Users was loaded";
                    cout << endl <<"[Press Enter.......]" << endl;
                    string buf;
                    getline(cin, buf);
                }
                loadStatus++;
                
            }
            if (status == 6)
            {
                identifyAgeCategories(table_);
            }
            if (status == 7)
            {
                break;
            }
        }
    }
}


int correctEnter()
{
    int value = 0;
    int check = scanf("%i", &value);
    if ((check == 0) || (value < 16))
    {
        system("clear");
        cout <<"###############################" << endl << endl;
        cout << "To use this application, your age must be over 16" << endl;
        cout << endl << "###############################" << endl;
        exit(1);
    }
    else return value;
}

void remove_menu(HashTable & table_)
{
    system("clear");
    string buf;
    Key newKey;
    cout << "Enter your username :" << endl;
    getline(cin, buf);
    newKey.username = buf;
    cout << "Enter your password :" << endl;
    getline(cin, buf);
    newKey.password = buf;
    if (table_.removeEntry(newKey))
        cout << endl << "User removed" << endl <<"[Press Enter.......]" << endl;
    else 
        cout << endl << "User not found" << endl <<"[Press Enter.......]" << endl;

    getline(cin, buf);
}

void insert_menu(HashTable & table_)
{
    system("clear");
    string buf;
    Key newKey;
    cout << "Enter your username :" << endl;
    getline(cin, buf);
    newKey.username = buf;
    cout << "Enter your password :" << endl;
    getline(cin, buf);
    newKey.password = buf;
    Value newVal;
    cout << "Enter your email address :" << endl;
    getline(cin, buf);
    newVal.emailAddress = buf;
    cout << "Enter your age :" << endl;
    newVal.age = correctEnter();
    Entiti newE{newKey, newVal};
    table_.insertEntry(newE);

    getline(cin, buf);
}

void find_menu(HashTable & table_)
{
    system("clear");
    string buf;
    Key newKey;
    cout << "Enter your username :" << endl;
    getline(cin, buf);
    newKey.username = buf;
    cout << "Enter your password :" << endl;
    getline(cin, buf);
    newKey.password = buf;
    optional<Value> val_opt = table_.findEntry(newKey);
    if (val_opt)
    {
        cout << endl <<"User found:" << endl;
        cout << "Email Address - " << val_opt.value().emailAddress << endl;
        cout << "Age - " << val_opt.value().age << endl;
    }
    else 
    {
       cout << endl <<"User not found" << endl; 
    }

    cout << endl <<"[Press Enter.......]" << endl;
    getline(cin, buf);
}

void printMenu(HashTable & table_)
{
    string buf;
    system("clear");
    table_.print(0);
    cout << endl << endl <<"[Press Enter.......]" << endl;
    getline(cin, buf);
}


void load(HashTable & table_)
{
        Key key;
        Value value;
        Entiti ent;
    for (int i = 1; i < 5; i++)
    {
        key.password = "pass" + to_string(i*1000);
        key.username = "usname" + to_string(i*10);
        value.emailAddress = "emailAddress@gmail.com" + to_string(i);
        value.age = rand()%60 + 1;
        ent.key = key;
        ent.value = value;
        table_.insertEntry(ent);
    }
}
