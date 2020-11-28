#include <iostream>
#include "graph.h"
#include "stack.h"
using namespace std;

int checkInput() {
    int n = 0; 
    int check = scanf("%i", &n);
    if (!check || n < 0)
        cout << "Please enter integers greater than 0." << endl;
    else 
        return n;
}

Stack &use(int status, Stack &A, Stack &B, Stack &C) {
    if (status == 1) return A;
    if (status == 2) return B;
    if (status == 3) return C;
}

bool complete(Stack &A, Stack &B, Stack &C) {
    if (A.empty() && B.empty() && C.sorted()) return true;
    else return false;
}

int main() {
    size_t n = 0;
    cout << "Enter number of disks: ";
    cin >> n;

   
    if (!cin.good() || n <= 0) cout << "Please enter an integer greater than 0." << endl;
    else {
        cout << "Enter " << n << " integers greater than 0. The first must be the biggest." << endl;

        Stack A{n};
        for (int i = 0; i < n; i++) {
            int buf = checkInput();
            if (buf > 0 && (buf < A.peek() || A.peek() == -1))
                A.push(buf);
            else {
                i--;
                cout << "Please enter integers less than the first one." << endl;
            }
        }

        cout << "Stack A is full. Let's start the game." << endl;
        
        Stack B{n}, C{n};
        int status1 = 0;
        int status2 = 0;
        while (true) {
            status1 = show(A, B, C, 0);
            status2 = show(A, B, C, status1);
            if (status1 && status2) {
                int buf = use(status1, A, B, C).peek();
                if (buf != -1) {
                    Stack &in = use(status2, A, B, C);
                    if (buf < in.peek() || in.peek() == -1) {
                        use(status1, A, B, C).pop();
                        in.push(buf);
                    }
                }
                if (complete(A, B, C)) break;
            }
        }
        cout << "You win!" << endl;
        cout << "A: ";
        A.print();
        cout << "B: ";
        B.print();
        cout << "C: ";
        C.print();
    }
}