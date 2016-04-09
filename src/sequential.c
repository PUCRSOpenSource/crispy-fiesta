#include <stdio.h>
#include <stdlib.h>

#define ROWS 1000
#define COLUMNS 100000

int matrix[ROWS][COLUMNS];

int compare(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

void populate_matrix() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = COLUMNS - j;
        }
    }
}

void sort_matrix() {
    for (int i = 0; i < ROWS; i++) {
        qsort(matrix[i], COLUMNS, sizeof(int), compare);
    }
}

int main() {
    populate_matrix();
//    sort_matrix();
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            printf("%d\n", matrix[i][j]);
        }
    }
    return 0;
}

