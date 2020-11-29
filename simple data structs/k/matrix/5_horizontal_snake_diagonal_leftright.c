#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main () {
    srand(time(0));
    int height, width;
    printf ("Enter integer height of matrix: ");
    scanf ("%i", &height); 
    printf ("Enter integer width of matrix: ");
    scanf ("%i", &width); 
    puts("");

    if(height != width)
        printf("Incorrect input. Height needs to be equal to width. Restart.\n");
    else if (height <= 0 || width <= 0)
        printf("Incorrect input. Height and width need to be larger that zero.\n");
    else {
        int matrix[height][width];

        int choice;
        printf("Enter 1 to process random matrix\nEnter 2 to process matrix with numbers from 0 to height*width\n");
        scanf("%d", &choice);
        if (choice == 1)
            for (int i = 0; i < height; i++)
                for (int j = 0; j < width; j++)
                    matrix[i][j] = rand() % (height * width + 1);
        else if (choice == 2) {
            int currElem = height * width;
            for (int i = 0; i < height; i++)
                for (int j = 0; j < width; j++) {
                    matrix[i][j] = height * width - currElem;
                    currElem--;
                }
        }
        else 
            printf("Incorrect choice input. Restart.\n");
        
        system("clear");
        puts("");

        int index[2] = {}; //array for indeces

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) 
                printf ("%i\t", matrix[i][j]);
            puts ("");
        }

        //1
        printf("1) Max element under main diagonal.\n");
        int maxL = matrix[height - 1][0];
        for (int cols = 0; cols < width; cols++) {
            if (cols % 2 == 1)
                for (int rows = cols + 1; rows < height; rows++) {
                    if (matrix[rows][cols] > maxL) {
                        maxL = matrix[rows][cols];
                        index[0] = rows;
                        index[1] = cols;
                    }
                    printf("%d[%d][%d] ", matrix[rows][cols], rows, cols);
                }
            else
                for (int rows = height - 1; rows > cols; rows--) {
                    if (matrix[rows][cols] > maxL) {
                        maxL = matrix[rows][cols];
                        index[0] = rows;
                        index[1] = cols;
                    }
                    printf("%d[%d][%d] ", matrix[rows][cols], rows, cols);
                }
        }
        printf("\nmax = %d[%d][%d]\n", maxL, index[0], index[1]);

        //2
        printf("2) Max and min element on main diagonal.\n");
        int maxD = matrix[height -1][width -1];
        int minD = matrix[0][0];
        int index2[2];
        for (int i = height - 1; i >= 0; i--) //i - rows j - cols
            for (int j = width - 1; j >= 0; j--) {
                if (i == j) {
                    if (matrix[i][j] < minD) {
                        minD = matrix[i][j];
                        index2[0] = i;
                        index2[1] = j;
                    }
                    else if (matrix[i][j] > maxD) {
                        maxD = matrix[i][j];
                        index[0] = i;
                        index[1] = j;
                    }
                    printf("%d[%d][%d] ", matrix[i][j], i, j);
                }
            }
        printf("\nmax = %d[%d][%d]\n", maxD, index[0], index[1]);
        printf("min = %d[%d][%d]\n", minD, index2[0], index2[1]);

        //3
        printf("3) Min element over main diagonal.\n");
        int minL = matrix[0][1];
        for (int rows = 0; rows < height - 1; rows++) {
            if (rows % 2 == 0)
                for (int cols = rows + 1; cols < width; cols++) {
                    if (matrix[rows][cols] < minL) {
                        minL = matrix[rows][cols];
                        index[0] = rows;
                        index[1] = cols;
                    }
                    printf("%d[%d][%d] ", matrix[rows][cols], rows, cols);
                }
            else 
                for (int cols = height - 1; cols > rows; cols--) {
                    if (matrix[rows][cols] < minL) {
                        minL = matrix[rows][cols];
                        index[0] = rows;
                        index[1] = cols;
                    }
                    printf("%d[%d][%d] ", matrix[rows][cols], rows, cols);
                }
        }
        printf("\nmin = %d[%d][%d]\n", minL, index[0], index[1]);
    }
}