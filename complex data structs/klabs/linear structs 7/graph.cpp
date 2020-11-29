#include "graph.h"

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

int show(Stack & A, Stack & B, Stack & C, int status)
{
    char key = 0;
    if (status == 0)
    {
        status = 100;
        while(1)
        {
            system("clear");              
            if (status == 1) cout << "->";
            cout << "A: ";
            A.print();
            if (status == 2) cout << "->";
            cout << "B: ";
            B.print();
            if (status == 3) cout << "->";
            cout << "C: ";
            C.print();
            key = getch();
            if (key == 'w')
            {
                if (status > 1) status--;
                if (status > 3) status = 1; //debug
            }
            if (key == 's')
            {
                if (status < 3) status++;
                if (status > 3) status = 1; //debug
            }
            if (key == '\n')
            {
                if (status != 100) return status;
            }
            //cout << endl << "st1 -" << status << endl;
        }
    } 
    else 
    {
        int status2 = 0;
        if (status != 1) status2 = 1;
        else status2 = 2;
        while(1)
        {
            system("clear");              
            if (status == 1) cout << "->";
            if (status2 == 1 && status != status2) cout << "->";
            cout << "A: ";
            A.print();
            if (status == 2) cout << "->";
            if (status2 == 2 && status != status2) cout << "->";
            cout << "B: ";
            B.print();
            if (status == 3) cout << "->";
            if (status2 == 3 && status != status2) cout << "->";
            cout << "C: ";
            C.print();
            key = getch();
            if (key == 'w')
            {
                if (status2 > 1) status2--;
                if (status2 == status)
                {
                    if (status == 1) status2++;
                    else status2--;
                }
            }
            if (key == 's')
            {
                if (status2 < 3) status2++;
                if (status2 == status)
                {
                    if (status == 3) status2--;
                    else status2++;
                }
            }
            if (key == '\n')
            {
                return status2;
            }
            //cout << endl << "st2 -" << status2 << endl;
        }
    }
}