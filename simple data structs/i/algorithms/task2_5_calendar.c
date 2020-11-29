#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int daysInM(int m, int y)
{
    int day_max = 0;
    if (m > 7) 
        m++;
    if (m % 2 == 0)
        day_max = 30;
    else 
        day_max = 31;
    if (m == 2)
        day_max = 28;
    if (((y % 4 == 0) && (y % 100 != 0) || (y % 400 == 0)) && (m == 2)) 
        day_max = 29;    
    return day_max;
}

bool chek(int d, int m, int y)
{
    int day_max = 0;
    if (m > 7) 
        m++;
    if (m % 2 == 0)
        day_max = 30;
    else 
        day_max = 31;
    if (m == 2)
        day_max = 28;
    if (((y % 4  == 0) && (y % 100 != 0) || (y % 400 == 0)) && (m == 2)) 
        day_max = 29;
    if ((m > 13) || (m < 1))
        return false;
    if (d < 1)
        return false;
    if (y < 1)
        return false;
    if (d > day_max)
        return false;
    
    return true;
}

int main()
{
    int d = 0;
    int m = 0;
    int y = 0;
    int daysbefore = 0;
    printf("Введіть день\n");
    scanf("%i", &d);
    printf("Введіть місяць\n");
    scanf("%i", &m);
    printf("Введіть рік\n");
    scanf("%i", &y);
    printf("Задана дата- %i.%i.%i \n", d, m, y);
    if (chek(d,m,y)) 
    {
        for (int i = 1; i < m; i++)
        {
            daysbefore += daysInM(i, y);
        }
        daysbefore += d;
        printf("Днів з початку року - %i\n", daysbefore);
        if ((y % 4 == 0) && (y % 100 != 0) || (y % 400 == 0))
            printf("Днів до кінця року- %i\n", 366 - daysbefore);
        else
            printf("Днів до кінця року- %i\n", 365 - daysbefore);
    }
    else 
        puts ("\n------------------------\nНевірно задана дата.\nПеревірте правильність введених даних.\n------------------------");
}