#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define KRED "\x1B[31m"
#define RESET "\x1B[0m"

int check_used(int x, int count, int used[]) {
    for (int i = 0; i < count; i++)
        if (used[i] == x)
            return 1;
    return 0;
}

void fillMatrix(size_t rows, size_t cols, int matrix[rows][cols], int K, int L, int color[rows][cols]) {
    int used[rows * cols];
    int count = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            while (true) {
                int r = rand() % (rows * cols) + 1; //0 to 100
                if (!check_used(r, count, used)) {
                    matrix[i][j] = used[count++] = r;
                    break;
                }
            }

            if (j % 2 == 1 && trunc(matrix[i][j] / K) < L)
                color[i][j] = 1;
            else 
                color[i][j] = 0;
        }
}

void printMatrix(size_t N, size_t M, int matrix[N][M], int color[N][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (color[i][j] == 0)
                printf("%d\t", matrix[i][j]);
            else 
                printf(KRED "%d\t" RESET, matrix[i][j]);
        }
        puts("");
    }
}

void cocktailSort(size_t count, int matrix[count]) {
    bool sorted = false;
    int start = 0;
    int end = count - 1;
    while (!sorted) {
        sorted = true;
        for (int i = start; i < end; i++) {
            if(arr[i] < arr[i + 1]) {
                int tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                sorted = false;
            }
        }

        if (sorted)
            break;
        sorted = true;
        end--;

        for (int i = end - 1; i >= start; i--) 
            if (arr[i] < arr[i + 1]) {
                int tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                sorted = false;
            }
        start++;
    }
}

void sortMatrix(size_t rows, size_t cols, int matrix[rows][cols], int K, int L, int color[rows][cols]) {
    int elems[rows * cols]; //nums to sort
    memset(elems, 0, rows * cols * sizeof(int));
    int counter = 0;
    int numberOfElems[cols]; //array of amounts in each column
    memset(numberOfElems, 0, cols * sizeof(int));

    for (int i = 0; i < rows; i++) 
        for(int j = 0; j < cols; j++)
            if (j % 2 == 1 && trunc(matrix[i][j] / K) < L) {
                color[i][j] = 1;
                elems[counter++] = matrix[i][j];
                numberOfElems[i]++;
            }

    cocktailSort(counter, elems);
    counter = 0;

    for (int j = 0; j < cols; j++)
        for (int i = 0; i < rows; i++)
            if(color[i][j] == 1)
                matrix[i][j] = elems[counter++];
}

int main() {
    srand(time(0));
    int N, M, K, L;
    printf("Enter number of rows: ");
    scanf("%d", &N);
    printf("Enter number of columns: ");
    scanf("%d", &M);
    printf("Enter K: ");
    scanf("%d", &K);
    printf("Enter L: ");
    scanf("%d", &L);

    if (N <= 1 || M <= 1)
        printf("Incorrect dimensions. Restart.\n");
    else if (K == 0)
        printf("Incorrect input. Restart.\n");
    else {
        int matrix[N][M];
        int color[N][M];
        fillMatrix(N, M, matrix, K, L, color);
        printMatrix(N, M, matrix, color);

        sortMatrix(N, M, matrix, K, L, color);
        puts("\nSorted:");
        printMatrix(N, M, matrix, color);
    }   
}
