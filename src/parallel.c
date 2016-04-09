#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 8
#define COLUMNS 20

int matrix[ROWS][COLUMNS];

int main(int argc, char *argv[])
{
	int my_rank;
	int proc_n;
	MPI_Status status;

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_n);
	if (my_rank == 0) {
		populate_matrix();
		for (i = 1; i < proc_n; ++i) {
			MPI_Send(matrix[i], COLUMNS,
					MPI_INT, i, MPI_ANY_TAG,
					MPI_COMM_WORLD);
		}
		for (i = 1; i < proc_n; ++i) {
			MPI_Recv(matrix[i], COLUMNS,
					MPI_INT, MPI_ANY_TAG,
					MPI_COMM_WORLD, &status);
			print_array(matrix[i]);
		}
	}
	else {
		int array[COLUMNS];
		MPI_Recv(array, COLUMNS,
				MPI_INT, 0, MPI_ANY_TAG,
				MPI_COMM_WORLD, &status);
		qsort(array, COLUMNS, sizeof(int), compare);
		MPI_Send(array, COLUMNS,
				MPI_INT, 0, MPI_ANY_TAG,
				MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}

void populate_matrix() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			matrix[i][j] = COLUMNS - j;
		}
	}
}
int compare(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}
void print_array(int[] array)
{
	for (i = 0; i < COLUMNS; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");
}
