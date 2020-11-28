#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define KRED "\x1B[31m"
#define KBLU "\x1B[34m"
#define RESET "\x1B[0m"

bool checkLetters(int L, char string[L]);
void print(int N, int L, char array[N][L], int color[N]);
void swap(int N, int L, char array[N][L], int index);
void bubbleSort(int N, int L, char array[N][L], int d, int order);
void LSDsort(int N, int L, char array[N][L], int color[N]);

int main() {
    int N = 0, L = 0, ch = 0;
    printf("Manual entering - 1\nSet example - 2\n");
    scanf("%d", &ch);
    if (ch==1) {
        printf("Enter number of strings: ");
        scanf("%d", &N);

        printf("Enter strings:\n1. ");
        char base[100];
        scanf("%s", base); //determine length based on first string
        L = strlen(base);
        char strings[N][L];
        strcpy(strings[0], base);

        int i = 1;
        while (i < N) {
            char tmp[100];
            printf("%d. ", i + 1);
            scanf("%s", tmp);
            if (strlen(tmp) != L) printf("Please enter strings of length %d.\n", L);
            else if (!checkLetters(L, tmp)) printf("Please enter strings consisting only of letters.\n");
            else {
                strcpy(strings[i], tmp);
                //printf("%s\n", strings[i]);
                i++;
            }
        }
        int color[N];
        memset(color, 0, N*sizeof(int));
        LSDsort(N, L, strings, color);
        print(N, L, strings, color);
    }
    else if (ch==2) {
        char setExample[5][3] = {"the", "man", "zin", "ark", "and"};
        int color[5] = {0, 1, 0, 1, 1};
        print(5, 3, setExample, color);
        puts("");
        LSDsort(5, 3, setExample, color);
        print(5, 3, setExample, color);
    }
    
}

bool checkLetters(int L, char string[L]) {
    bool allLetters = true;
    for (int i = 0; i < L - 1; i++) {
        if(!isalpha(string[i])) {
            allLetters = false;
            break;
        }
    }
    return allLetters;
}

void print(int N, int L, char array[N][L], int color[N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < L; j++) {
            if (color[i]) printf(KRED "%c" RESET, array[i][j]);
            else printf(KBLU "%c" RESET, array[i][j]);
        }
        puts("");
    }
}

void swap(int N, int L, char array[N][L], int index) {
    char tmp[L];
    strncpy(tmp, array[index], L);
    strncpy(array[index], array[index - 1], L);
    strncpy(array[index - 1], tmp, L);
}

void bubbleSort(int N, int L, char array[N][L], int d, int order) {
    if (order) {
        for (int i = 0; i < N; i++) 
            for (int j = 1; j < N - i; j++)
                if (array[j-1][d] > array[j][d]) 
                    swap(N, L, array, j);  
    } 
    else {
        for (int i = 0; i < N; i++) 
            for (int j = 1; j < N - i; j++)
                if (array[j-1][d] < array[j][d]) 
                    swap(N, L, array, j);  
    }
    
}

void LSDsort(int N, int L, char array[N][L], int color[N]) {
    int firstCount = 0, secondCount = 0;
    
    for (int i = 0; i < N; i++) {
        if ((array[i][0] >= 65 && array[i][0] <= 77) || (array[i][0] >= 97 && array[i][0] <= 109)) {
            color[i] = 1;
            firstCount++;
        }
        else {
            color[i] = 0;
            secondCount++;
        }
    }
    char firstArray[firstCount][L];
    char secondArray[secondCount][L];

    int n = 0, m = 0;
    for (int i = 0; i < N; i++) {
        if (color[i] == 1) strcpy(firstArray[n++], array[i]);
        else if (color[i] == 0) strcpy(secondArray[m++], array[i]);
    }

    for (int d = L - 1; d >= 0; d--) {
        bubbleSort(firstCount, L, firstArray, d, 1);
        bubbleSort(secondCount, L, secondArray, d, 0);
    }

    n = 0, m = 0;
    for (int i = 0; i < N; i++) {
        if (color[i]) strcpy(array[i], firstArray[n++]);
        else strcpy(array[i], secondArray[m++]);
    }
}
