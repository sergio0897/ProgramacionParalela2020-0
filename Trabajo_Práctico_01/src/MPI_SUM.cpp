#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int rangoBase = 0;

    int miRango;
    MPI_Comm_rank(MPI_COMM_WORLD, &miRango);

    int reduction_result = 0;
    MPI_Reduce(&miRango, &reduction_result, 1, MPI_INT, MPI_SUM, rangoBase, MPI_COMM_WORLD);

    if(miRango == rangoBase)
    {
        printf("La suma de todos es %d.\n", reduction_result);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
