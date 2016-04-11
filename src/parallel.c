#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 8
#define COLUMNS 20

#define WORK_TAG 1
#define SUICIDE_TAG 2

int matrix[ROWS][COLUMNS];

void populate_matrix() {
    int i;
    int j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            matrix[i][j] = COLUMNS - j;
        }
    }
}

int compare(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

void print_array(int array[]) {
    int i;
    for (i = 0; i < COLUMNS; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int i;
    int my_rank;
    int proc_n;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_n);

    if (my_rank == 0) {
        populate_matrix();
        // Send messages.
        for (i = 1; i < proc_n; ++i) {
            MPI_Send(matrix[i], COLUMNS,
                     MPI_INT, i, WORK_TAG,
                     MPI_COMM_WORLD);
        }
        // Get answers.
        for (i = 1; i < proc_n; ++i) {
            MPI_Recv(matrix[i], COLUMNS,
                     MPI_INT, i, WORK_TAG,
                     MPI_COMM_WORLD, &status);
            print_array(matrix[i]);

        }
        // Send kill signal.
        for (i = 1; i < proc_n; ++i) {
            MPI_Send(0, 0, MPI_INT, i, SUICIDE_TAG, MPI_COMM_WORLD);
        }
    }
    else {
        int array[COLUMNS];
        while (1) {
            MPI_Recv(array, COLUMNS,
                     MPI_INT, 0, MPI_ANY_TAG,
                     MPI_COMM_WORLD, &status);
            if (status.MPI_TAG == 2) {
                MPI_Finalize();
                return 0;
            }
            qsort(array, COLUMNS, sizeof(int), compare);
            MPI_Send(array, COLUMNS,
                     MPI_INT, 0, WORK_TAG,
                     MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}

