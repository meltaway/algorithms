#include "hashmap.h"
#include <unistd.h>
using namespace std;

int main() {
    HashTable table(10);
    int k = 0, pos = 0;
    while (true) {
        system("clear");
        show(pos);
        k = getch();
        if (k == 'w' && pos > 0) {//up
            pos--;
            show(pos);
        }
        else if (k == 's' && pos < 3) { //down
            pos++;
            show(pos);
        }
        else if (k == 'q') {
            k = 0;
            if (pos == 0) { //add
                system("clear");
                Key key;
                cout << "Enter first name, last name, student ID." << endl;
                cin >> key.firstName >> key.lastName >> key.studentID;
                cout << "Enter more info about the student:" << endl;
                Value value;
                cout << "Birth date (dd/mm/yyyy): ";
                getline(cin, value.birthDate);
                cout << "Address: ";
                getline(cin, value.address);
                cout << "Year of entry: ";
                cin >> value.yearOfEntry;
                cout << "Number of disciplines: ";
                int n = 0;
                cin >> n;
                cout << "Enter discipline names and grades:" << endl;
                for (int i = 0; i < n; i++) {
                    Discipline subject;
                    getline(cin, subject.disciplineName);
                    cin >> subject.grade;
                    updateDisciplinesList(value, subject, true);
                }
                table.insertEntry(key, value);
                sleep(2);
                char c = getch();
                if (c == ' ') continue;
            }
            else if (pos == 1) { //delete
                system("clear");
                Key key;
                cout << "Enter first name, last name and student ID of student to delete." << endl;
                cin >> key.firstName >> key.lastName >> key.studentID;
                table.removeEntry(key);
                table.print();
                sleep(2);
                char c = getch();
                if (c == ' ') continue;
            }
            else if (pos == 2) { //find
                system("clear");
                Key key;
                cout << "Enter first name, last name and student ID of student to find." << endl;
                cin >> key.firstName >> key.lastName >> key.studentID;
                Value found = table.findEntry(key);
                if (found.averageGrade != -1) { //edit subjects
                    cout << key.firstName << " " << key.lastName << " [" << key.studentID << "]" << endl;
                    cout << "INFO:\nBirthdate: " << found.birthDate << "\nAddress: " << found.address << "\nYear of entry: " << found.yearOfEntry << "\nDisciplines:" << endl;
                    printDisciplines(found.disciplines);
                    char yn = 0;
                    cout << "Do you want to edit the discipline list? [y/n]: ";
                    cin >> yn;
                    if (yn == 'y') {
                        string answer;
                        printDisciplines(found.disciplines);
                        cout << "Delete or add discipline? [delete/add]: ";
                        getline(cin, answer);
                        string discName;
                        cout << "Enter the name of the discipline: " << endl;
                        cin >> discName;
                        if (answer == "delete") {
                            struct Discipline toDelete = findDiscipline(discName, found.disciplines);
                            if (toDelete.grade != -1) {
                                cout << "Deleting discipline..." << endl;
                                updateDisciplinesList(found, toDelete, false);
                                cout << "Discipline deleted." << endl;
                                printDisciplines(found.disciplines);
                            }
                        }
                        else if (answer == "add") {
                            struct Discipline toAdd = findDiscipline(discName, found.disciplines);
                            if (toAdd.grade != -1) {
                                cout << "Adding discipline..." << endl;
                                updateDisciplinesList(found, toAdd, true);
                                cout << "Discipline added." << endl;
                                printDisciplines(found.disciplines);
                            }
                        }
                    }
                }
                sleep(2);
                char c = getch();
                if (c == ' ') continue;
            }
            else if (pos == 3) { //print
                system("clear");
                table.print();
                char c = getch();
                if (c == ' ') continue;
            }
        }

    }
}