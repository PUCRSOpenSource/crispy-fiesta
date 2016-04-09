#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 16
#define COLUMNS 20
#define MIN(a,b) (((a)<(b))?(a):(b))

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

void print_array(int array[])
{
	int i;
	for (i = 0; i < COLUMNS; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	int i;
	int my_rank;
	int proc_n;
	MPI_Status status;
	int max_workers;
	int to_work = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_n);
	if (my_rank == 0) {
		populate_matrix();

		while(has_work) {
			max_workers = MIN(ROWS - to_work, proc_n);
			for (i = 1; i < max_workers; ++i) {
				MPI_Send(matrix[to_work], COLUMNS,
						 MPI_INT, i, 1,
						 MPI_COMM_WORLD);
			}
			for (i = 1; i < max_workers; ++i) {
				MPI_Recv(matrix[i], COLUMNS,
						 MPI_INT, i, 1,
						 MPI_COMM_WORLD, &status);
				printf("i: %d -> ", i);
				print_array(matrix[i]);
			}
			has_work = to_work < ROWS;
		}
	}
	else {
		int array[COLUMNS];
		MPI_Recv(array, COLUMNS,
				MPI_INT, 0, 1,
				MPI_COMM_WORLD, &status);
		qsort(array, COLUMNS, sizeof(int), compare);
		MPI_Send(array, COLUMNS,
				MPI_INT, 0, 1,
				MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}

