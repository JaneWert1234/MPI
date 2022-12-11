#include <iostream>
#include <cstdio>
#include "mpi.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char** argv)
{
    int rank, size, count;
    const int N = 10;
    int a[N];
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 1) {
        for (int i = 0; i < 10; ++i) a[i] = rand() % 100;
        MPI_Send(&a, 10, MPI_INT, 0, 100, MPI_COMM_WORLD);
        MPI_Send(&a, 10, MPI_INT, 2, 100, MPI_COMM_WORLD);
        MPI_Send(&a, 10, MPI_INT, 3, 100, MPI_COMM_WORLD);
    }
    else {
        MPI_Probe(1, 100, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        MPI_Recv(&a, count, MPI_INT, 1, 100, MPI_COMM_WORLD, &status);
        stringstream ss;
        ss << "Process: " << rank << " Size: " << size << "\n";
        for (int i = 0; i < 10; i++) {
            ss << a[i] << " ";
        }
        ss << "\n";
        cout << ss.str();
    }
    MPI_Finalize();
}
