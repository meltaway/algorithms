#include <stdio.h>
#include <math.h>

int main()
{
    float const pi = 3.14159265358979;
    float x = 0;
    float y = 0;
    float z = 0;
    float a = 0;
    float b = 0;
    printf("Введіть х\n");
    scanf("%f", &x);
    printf("Введіть у\n");
    scanf("%f", &y);
    printf("Введіть z\n");
    scanf("%f", &z);

    if((pow(x,2) != z) && (x != z) && (z != 0))
    {
        a = log10(fabs(pow(x,2) - z)) + sin(y + cos(x));
        b = (a - cos(a/z)) * pi * a / fabs(z - x); 
        printf("a = %f\n", a);
        printf("b = %f\n", b);
    }
    else printf("Помилка. Введені дані не задовольняють ОДЗ\n x^2 != z\n x != z\n z != 0\n");
    }