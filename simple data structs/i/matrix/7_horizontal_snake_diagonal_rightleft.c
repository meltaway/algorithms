#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() 
{
    srand(time(0));
    printf("Enter matrix size\n");
    int N = 0;
    scanf("%i", &N);
    int mrx[N][N];
    int max1 = 0;
    int max2 = 0;
    int max3 = 0;
    int min1 = __INT_MAX__;
    int min2 = __INT_MAX__;
    int min3 = __INT_MAX__;
    int maxx1, maxy1, minx1, miny1, maxx2, maxy2, minx2, miny2, maxx3, maxy3, minx3, miny3; 
    for (int i = 0; i < N; i++)
    {
        for (int x = 0; x < N; x++)
        {
            mrx[i][x] = rand()% (N * N) + 0;
            if (mrx[i][x] > 9)
                printf("%i ", mrx[i][x]);
            else 
                printf(" %i ", mrx[i][x]);
        }
        puts("");
    }
    puts("");

    int c = 0;
    for (int i = N - 2; i >= 0; i--)
    {
        if ((c % 2) == 0)
        {
            for (int x = (N - 2 - i); x >= 0; x--)
            {
                if (mrx[i][x] > max1)
                {
                    max1 = mrx[i][x];
                    maxx1 = i;
                    maxy1 = x;
                }
                if (mrx[i][x] < min1)
                {
                    min1 = mrx[i][x];
                    minx1 = i;
                    miny1 = x;
                }
                printf("%i ", mrx[i][x]);
            }
        }
        else 
        {
            for (int x = 0; x < (N - 1 - i); x++)
            {
                if (mrx[i][x] > max1)
                {
                    max1 = mrx[i][x];
                    maxx1 = i;
                    maxy1 = x;
                }
                if (mrx[i][x] < min1)
                {
                    min1 = mrx[i][x];
                    minx1 = i;
                    miny1 = x;
                }
                printf("%i ", mrx[i][x]);
            }
        }
        c++;
        printf(" ");
    }

    puts("");
    int j = N - 1;
    for(int i = 0; i < N; i++)
    {
        if (mrx[i][j] > max2)
        {
            max2 = mrx[i][j];
            maxx2 = i;
            maxy2 = j;
        }
        if (mrx[i][j] < min2)
        {
            min2 = mrx[i][j];
            minx2 = i;
            miny2 = j;
        }
        printf("%i ", mrx[i][j]);
        j--;
    }

    puts("");
    int c2 = 0;
    for (int x = 1; x < N; x++)
    {
        if ((c2 % 2) == 0)
        {
            for (int i = N - 1; i >= (N - x); i--)
            {
                if (mrx[i][x] > max3)
                {
                    max3 = mrx[i][x];
                    maxx3 = i;
                    maxy3 = x;
                }
                if (mrx[i][x] < min3)
                {
                    min3 = mrx[i][x];
                    minx3 = i;
                    miny3 = x;
                }
                printf("%i ", mrx[i][x]);
            }
        }
        else 
        {
            for (int i = (N - x); i < N  ; i++)
            {
                if (mrx[i][x] > max3)
                {
                    max3 = mrx[i][x];
                    maxx3 = i;
                    maxy3 = x;
                }
                if (mrx[i][x] < min3)
                {
                    min3 = mrx[i][x];
                    minx3 = i;
                    miny3 = x;
                }
                printf("%i ", mrx[i][x]);
            }
        }
        c2++;
        printf(" ");
    }
    puts("");
    printf ("Максимальне в 1 частині - %i(%i,%i)    Максимальне в 2 частині - %i(%i,%i)   Максимальне в 3 частині - %i(%i,%i)\nМінімальне в 1 частині - %i(%i,%i)   Мінімальне в 2 частині - %i(%i,%i)   Мінімальне в 3 частині - %i(%i,%i)\n", max1, maxx1 + 1, maxy1 + 1, max2, maxx2 + 1, maxy2 + 1, max3, maxx3 + 1, maxy3 + 1, min1, minx1 + 1, miny1 + 1, min2, minx2 + 1, miny2 + 1, min3, minx3 + 1, miny3 + 1);
}