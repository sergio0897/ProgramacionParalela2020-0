#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int rangoBase = 0;

    int miRango;
    MPI_Comm_rank(MPI_COMM_WORLD, &miRango);

    int resultado = 0;
    MPI_Reduce(&miRango, &resultado, 1, MPI_INT, MPI_MIN, rangoBase, MPI_COMM_WORLD);

    if(my_rank == rangoBase)
    {
        printf("El mínimo de todos es %d.", resultado);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
