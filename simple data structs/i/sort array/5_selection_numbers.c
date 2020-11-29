#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define KGRN "\x1B[32m"
#define RESET "\x1B[0m"

void arrprint(int *arr, int *arr2, size_t arrlen);
void arrrandom(int *arr, int *arr2, size_t arrlen, int range);
void decadesort(int *arr, size_t arrlen);
void centurysort(int *arr, size_t arrlen);

void swap(int * a, int * b);

bool isdecade(int * number);
bool iscentury(int * number);

int main()
{
    srand(time(0));
    printf("Enter size\n");
    int N = 0;
    int chek = scanf("%i", &N);
    if ((chek == 0) || (N < 1))
    {
        printf("Please enter int numbers > 0\n");
        exit(1);
    }
    int arr[N];
    int arr2[N];
    printf("Enter range for random numbers\n");
    chek = 0;
    int range = 0;
    chek = scanf("%i", &range);
    if ((chek == 0) || (range < 1)) 
    {
        printf("Please enter int numbers > 0\n");
        exit(1);
    }
    if (range <= N/2)
    {
        printf("Range of numbers must be bigger than array size / 2\n");
        exit(1);
    }
    arrrandom(arr, arr2, N, range);
    decadesort(arr, N);
    centurysort(arr, N);
    arrprint(arr, arr2, N);
}


void swap(int * a, int * b)
{
    int buf = *b;
    *b = *a;
    *a = buf; 
}

bool isdecade(int * number)
{
    if ((*number > 9) && (*number < 100)) return true;
    if ((*number < -9) && (*number > -100)) return true;
    return false;
}

bool iscentury(int * number)
{
    if ((*number > 99) && (*number < 1000)) return true;
    if ((*number < -99) && (*number > -1000)) return true;
    return false;
}

void decadesort(int *arr, size_t arrlen)
{
    int min = 0;
    for (int i = 0; i < arrlen - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < arrlen; j++)
        {
            if ((arr[j] < arr[min]) && (isdecade(&arr[j])) && (isdecade(&arr[min]))) 
            {
                min = j;
            }
        }
        if (i != min) swap(&arr[i], &arr[min]);
    }
}

void centurysort(int *arr, size_t arrlen)
{
    int max = 0;
    for (int i = 0; i < arrlen - 1; i++)
    {
        max = i;
        for (int j = i + 1; j < arrlen; j++)
        {
            if ((arr[j] > arr[max]) && (iscentury(&arr[j])) && (iscentury(&arr[max]))) 
            {
                max = j;
            }
        }
        if (i != max) swap(&arr[i], &arr[max]);
    }
}

void arrprint(int *arr,int *arr2, size_t arrlen)
{
    for (int i = 0; i < arrlen; i++)
    {
        if (arr[i] == arr2[i])
        {
            printf(KGRN "%i " RESET, arr2[i]);
        }
        else printf("%i ", arr2[i]);
    }
    puts("");

    for (int i = 0; i < arrlen; i++)
    {
        if (arr[i] == arr2[i])
        {
            printf(KGRN "%i " RESET, arr[i]);
        }
        else printf("%i ", arr[i]);
    }
    puts("");
}

void arrrandom(int *arr, int *arr2, size_t arrlen, int range)
{
    int counter = 0;
    int c = 0;
    for (int i = 0; i < arrlen; i++)
    {
        counter = rand() % 2 + 0;
        if (counter == 1) arr[i] = rand() % range + 0;
        if (counter == 0) arr[i] = -rand() % range + 0;
        arr2[i] = arr[i];
        for (int j = 0; j < i; j++)
        {
            if (arr[i] == arr[j]) c++;
        }
        if (c != 0)
        {
            i--;
            c = 0;
        }
    }
}