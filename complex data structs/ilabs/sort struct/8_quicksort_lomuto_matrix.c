#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <progbase.h>
#include <progbase/console.h>

#define KGRN "\x1B[32m"
#define RESET "\x1B[0m"
#define KRED "\x1B[31m"

//private
int correctEnter();
void graphic(int N, int M, int * matrix);
void randomizeMatrx(int N, int M, int matrix[N][M], int range);
int randomOne(int range);
bool CheckMatrix(int N, int M, int matrix[N][M], int value);

//public
void swap(int * A, int * B);
void quickSort(int arr[], int low, int high, int status);
int separator(int arr[], int low, int high, int status);

int main()
{
    srand(time(0));
    system("clear");
    printf("1 - random\n2 - example\n");
    int menu = correctEnter();
    system("clear");
    printf("-----Enter Height\n");
    int N = correctEnter();
    system("clear");
    graphic(N, 0, NULL);
    printf("-----Enter Width\n");
    int M = correctEnter();
    system("clear");
    graphic(N, M, NULL);
    int matrix[N][M];
    if( menu == 1)
    {
        printf("-----Enter range\n");
        int range = correctEnter();
        system("clear");
        randomizeMatrx(N, M, matrix, range);
    } else if (menu == 2)
    {
        for (int i = 0; i < N; i++)
        {
            printf("Line %i ----\n", i);
            for (int j = 0; j < M; j++)
            {
                scanf("%i", &matrix[i][j]);
            }
        }
        system("clear");
    }
    
    int * pointerMtrx = * matrix;
    graphic(N, M, pointerMtrx);

    ////
    for (int i = 0; i < N; i++)
    {
        int arr[M];
        for (int j = 0; j < M; j++)
        {
            arr[j] = matrix[i][j];
        }

        if (i != 0 && i != N - 1 && i != N / 2) quickSort(arr, 0, M - 1, 1);
        else quickSort(arr, 0, M - 1, 0);

        for (int j = 0; j < M; j++)
        {
            matrix[i][j] = arr[j];
        }
    }
    printf("\n--------Sorted:\n\n");
    graphic(N, M, pointerMtrx);
}

//public

void swap(int * A, int * B)
{
    int buf = *A;
    *A = *B;
    *B = buf;
}

int separator(int arr[], int low, int high, int status) 
{ 
    int pivot = arr[high];   
    int i = (low - 1);  
  
    for (int j = low; j <= high - 1; j++) 
    { 
        if (status == 1)
        {
            if (arr[j] <= pivot) 
            { 
                i++; 
                swap(&arr[i], &arr[j]); 
            } 
        }
        else 
        {
            if (arr[j] >= pivot) 
            { 
                i++; 
                swap(&arr[i], &arr[j]); 
            } 
        }
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
  
void quickSort(int arr[], int low, int high, int status) 
{ 
    if (low < high) 
    { 
        int num = separator(arr, low, high, status); 
        quickSort(arr, low, num - 1, status); 
        quickSort(arr, num + 1, high, status); 
    } 
} 


// privat
int correctEnter()
{
    int value = 0;
    int check = scanf("%i", &value);
    if ((check == 0) || (value < 1))
    {
        printf("Please enter int numbers > 0\n");
        exit(1);
    }
    else return value;
}

void graphic(int N, int M, int * matrix)
{
    int timeR = 5;
    if (M == 0)
    {
        for(int i = 0; i < N; i++)
        {
        printf("0\n");
        sleepMillis(timeR);
        }
    }
    else if (matrix == NULL)
    {
        for (int i = 1; i <= N * M; i++)
        {
        printf("0\t");
        if (i % M == 0) puts("");
        sleepMillis(timeR / 5);
        }
    }
    else
    {
        int numLine = 0;
        for (int i = 1; i <= N * M; i++)
        {
            if (numLine == 0 || numLine == N / 2 || numLine == N - 1)
                printf(KRED "%02i\t" RESET, matrix[i - 1]);
            else 
                printf(KGRN "%02i\t" RESET, matrix[i - 1]);
            if (i % M == 0)
            {
                numLine++;
                puts("");
            }
            sleepMillis(timeR);
        }
    }
}

void randomizeMatrx(int N, int M, int matrix[N][M], int range)
{
    if (range <= N * M / 2)
    {
        printf("Range must be > N*M / 2\n");
        exit(1);
    }
    for (int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            int buf = randomOne(range);
            if (!CheckMatrix(N, M, matrix, buf)) matrix[i][j] = buf;
            else j = -1; 
        }
    }
}

int randomOne(int range)
{
    int counter = rand() % 2 + 0;
    if (counter == 1) return rand() % range + 0;
    if (counter == 0) return -rand() % range + 0;
}  

bool CheckMatrix(int N, int M, int matrix[N][M], int value)
{
    for (int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if (matrix[i][j] == value) return true;
        }
    }  
    return false;
}