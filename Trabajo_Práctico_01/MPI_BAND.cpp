#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int rangoBase = 0;

    int miRango;
    MPI_Comm_rank(MPI_COMM_WORLD, &miRango);

    char valores[4] = {0, 1, 3, 8};
    char miValor = valores[miRango];
    char resultado = 0;
    MPI_Reduce(&miValor, &resultado, 1, MPI_UNSIGNED_CHAR, MPI_BAND, rangoBase, MPI_COMM_WORLD);

    if(miRango == rangoBase)
    {
        printf("El valor bit a bit de los valores es %d.", resultado);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
