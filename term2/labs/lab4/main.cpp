#include "third.h"
#include <stdlib.h>
#include <time.h>
 
int main(){
    srand(time(0));

    Tree *tree = (struct Tree*)malloc(sizeof(Tree*));
    tree->root=nullptr;

    while (1) {
        cout << endl << endl;
        printNode(tree->root, ' ', 0);
        cout << "Enter A to add node, D to delete, Q to quit: ";
        char ch;
        cin >> ch;
        if (ch == 'a') {
            int num = 0;
            cout << "Enter number to add to the tree: ";
            cin >> num;
            if (!insert(tree, num)) cout << "Could not insert." << endl;
        }
        else if (ch == 'd') {
            int num = 0;
            cout << "Enter number to delete from the tree: ";
            cin >> num;
            if (!remove(tree, num)) cout << "Could not remove." << endl;
        }
        else if (ch == 'q')
            break;        
    }
}