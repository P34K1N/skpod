#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char * argv[]) {
    MPI_Init(&argc, &argv);

    const int N = 10;

    double matrix[N][N];
    double mypart[N][N];
    int part_size = 1; // stores how many cols a process needs to work on

    int myrank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (myrank == 0) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                matrix[i][j] = i * 10 + j;
                mypart[i][j] = 0;
            }
        }
    }

    MPI_Datatype col, coltype;
    MPI_Type_vector(N, 1, N, MPI_DOUBLE, &col);
    MPI_Type_commit(&col);
    MPI_Type_create_resized(col, 0, 1*sizeof(double), &coltype);
    MPI_Type_commit(&coltype);
    MPI_Scatter(matrix, part_size, coltype,
              mypart, part_size * N, MPI_DOUBLE,
              0, MPI_COMM_WORLD);
    if (myrank == 0) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                printf("%lf ", mypart[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
}
