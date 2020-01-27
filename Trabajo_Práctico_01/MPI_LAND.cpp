#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int rangoBase = 0;

    int miRango;
    MPI_Comm_rank(MPI_COMM_WORLD, &miRango);

    bool miValor = (miRango != 3);
    bool resultado = false;
    MPI_Reduce(&miValor, &resultado, 1, MPI_C_BOOL, MPI_LAND, rangoBase, MPI_COMM_WORLD);

    if(miRango == rangoBase)
    {
        printf("La lógica de los valores es %s.", resultado ? "true" : "false");
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
