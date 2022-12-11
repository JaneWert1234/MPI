#include <iostream>
#include <cstdio>
#include "mpi.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <random>
#include <math.h>

int main(int argc, char** argv)
{
    int rank, word_size;
    MPI_Status status;
    
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &word_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int N = 12;
    const int block = 3;
    assert(word_size == 5);
    if (rank == 0) {
        int x[N];
        int y[N];
        int z1[N];
        int z2[N];
        for (int i = 0; i < N; ++i) {
            x[i] = rand() % 10;
            y[i] = rand() % 10;
        }
        for (int i = 0; i < N; ++i) {
            printf("%d ", x[i]);
        }
        printf("\n");
        for (int i = 0; i < N; ++i) {
            printf("%d ", y[i]);
        }
        printf("\n");
        for (int i = 1; i < word_size; i++) {
            MPI_Send(&x[(i - 1) * block], block, MPI_INT, i, 10, MPI_COMM_WORLD);
            MPI_Send(&y[(i - 1) * block], block, MPI_INT, i, 10, MPI_COMM_WORLD);
        }

        for (int i = 1; i < word_size; i++) {
            MPI_Recv(&z1[(i - 1) * block], block, MPI_INT, i, 100, MPI_COMM_WORLD, &status);

            MPI_Recv(&z2[(i - 1) * block], block, MPI_INT, i, 1000, MPI_COMM_WORLD, &status);

        }

        printf("Z1: ");
        for (int i = 0; i < 12; ++i) printf(" %d  ", z1[i]);

        printf("\nZ2: ");
        for (int i = 0; i < 12; ++i) printf(" %d  ", z2[i]);

        }
    else {
        int x[block];
        int y[block];
        int z1[block];
        int z2[block];
        MPI_Recv(&x, block, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        MPI_Recv(&y, block, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);

        
        for (int i = 0; i < block; ++i) {
            z1[i] = x[i] + y[i];
        }

        MPI_Send(&z1, block, MPI_INT, 0, 100, MPI_COMM_WORLD);

        for (int i = 0; i < block; i++) {
            z2[i] = x[i] * y[i];
        }

        MPI_Send(&z2, block, MPI_INT, 0, 1000, MPI_COMM_WORLD);

        }
    MPI_Finalize();
    return 0;

}
