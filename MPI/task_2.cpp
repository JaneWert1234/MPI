#include <iostream>
#include <cstdio>
#include <random>
#include "mpi.h"



int main(int argc, char** argv)
{
    int rank;
    const int N = 10;
    int a[N];
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    srand(time(0));

    if (rank == 0) {
        for (int i = 0; i < N; ++i) a[i] = rand();
        MPI_Send(a, N, MPI_INT, 1, 100, MPI_COMM_WORLD);
    }
    else {
        MPI_Recv(a, N, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
        for (int i = 0; i < N; i++)
            printf("%d\n", a[i]);
    }
    MPI_Finalize();
    return 0;

}

