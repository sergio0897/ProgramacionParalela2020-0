#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int rangoBase = 0;

    int miRango;
    MPI_Comm_rank(MPI_COMM_WORLD, &miRango);

    int miValor = miRango + 1;
    int resultado = 0;
    MPI_Reduce(&miValor, &resultado, 1, MPI_INT, MPI_PROD, rangoBase, MPI_COMM_WORLD);

    if(miRango == rangoBase)
    {
        printf("El producto de los valores es %d.", resultado);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
