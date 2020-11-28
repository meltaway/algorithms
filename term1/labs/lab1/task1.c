#include <stdio.h>
#include <math.h>

int main() {
    float x, y, z;
    printf("Enter x, y, z:\n");
    scanf("%f", &x);
    scanf("%f", &y);
    scanf("%f", &z);

    if (z == 0)
        printf("ERROR\n");
    else if (1 + pow(x, 2) / 2 + pow(y, 2) / 4 == 0)
        printf("ERROR\n");
    else {
        float a = (sqrt(fabs(x-1)) - pow(y, 1/3)) / (1 + pow(x, 2) / 2 + pow(y, 2) / 4);
        if (a <= 0)
            printf("ERROR\n");
        else {
            float b = x * (1 / pow(z, 4) + 1 / pow(a, x+3));
            printf("a = %f\n", a);
            printf("b = %f\n", b);
        }
    }
}