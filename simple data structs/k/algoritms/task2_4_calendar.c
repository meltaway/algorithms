#include <stdio.h>

int calcDays(int m);
int calcDiff(int d, int m);
int checkInput(int d, int m);

int main() {
    int d, m;
    printf("Enter day: ");
    scanf("%d", &d);
    printf("Enter month: ");
    scanf("%d", &m);

    int check = checkInput(d, m);
    if (check == 0)
        printf("Incorrect input.\n");
    else {
        int day = calcDiff(d, m) % 7;
        switch (day) {
        case 0:
            printf("%d.%d is a Wednesday.\n", d, m);
            break;
        case 1:
            printf("%d.%d is a Thursday.\n", d, m);
            break;
        case 2:
            printf("%d.%d is a Friday.\n", d, m);
            break;
        case 3:
            printf("%d.%d is a Saturday.\n", d, m);
            break;
        case 4:
            printf("%d.%d is a Sunday.\n", d, m);
            break;
        case 5:
            printf("%d.%d is a Monday.\n", d, m);
            break;
        case 6:
            printf("%d.%d is a Tuesday.\n", d, m);
            break;
        }
    }
}

int calcDays(int m)
{
    if (m > 8)
        m++;
    if (m % 2 == 1)
        return 31;
    else
        return 30;
}

int calcDiff(int d, int m)
{
    int res = 0;
    for (int i = 1; i < m; i++)
    {
        if (i == 2)
            res += 28;
        else
            res += calcDays(i);
    }
    return res + d;
}

int checkInput(int d, int m)
{
    int days = calcDays(m);
    if (d <= 28)
        return 1;
    else if (m == 2)
        return 0;
    else if (days == 31)
    {
        if (d <= 31)
            return 1;
        else
            return 0;
    }
    else
    {
        if (d <= 30)
            return 1;
        else
            return 0;
    }
}