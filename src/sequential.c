#include<stdio.h>
#define ROWS 1000
#define COLUMNS 100000

int matrix[ROWS][COLUMNS];

int main()
{
    int i = 0;
    int j = 0;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            matrix[i][j] = COLUMNS - j;
        }
    }

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            printf("%d\n", matrix[i][j]);
        }
    }
    return 0;
}

