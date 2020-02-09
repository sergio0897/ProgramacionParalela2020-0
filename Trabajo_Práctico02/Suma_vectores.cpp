#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

#define miRango 0
#define RECV 1
#define SUM 2

void llenarArreglo(int VECTOR[], int MAX);
void imprimirArreglo(int VECTOR[], int MAX);

int main(int argc, char *argv[])
{
	int rank, size;
	int MAX = atoi(argv[1]);
	int VECTOR_A[MAX], VECTOR_B[MAX];

	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == miRango)
	{
		llenarArreglo(VECTOR_A, MAX);
		llenarArreglo(VECTOR_B, MAX);

		MPI_Send(VECTOR_A, MAX, MPI_INT, RECV, 2, MPI_COMM_WORLD);
		MPI_Send(VECTOR_B, MAX, MPI_INT, RECV, 3, MPI_COMM_WORLD);
	}
	else
	{
		if (rank == RECV)
		{
			MPI_Recv(VECTOR_A, MAX, MPI_INT, miRango, 2, MPI_COMM_WORLD, &status);

			MPI_Recv(VECTOR_B, MAX, MPI_INT, miRango, 3, MPI_COMM_WORLD, &status);


			printf("Vector A :\n");imprimirArreglo(VECTOR_A, MAX);
			printf("Vector B:\n");imprimirArreglo(VECTOR_B, MAX);


			MPI_Send(VECTOR_A, MAX, MPI_INT, SUM, 2, MPI_COMM_WORLD);

			MPI_Send(VECTOR_B, MAX, MPI_INT, SUM, 3, MPI_COMM_WORLD);
		}
		else
		{
			if (rank == SUM)
			{
				MPI_Recv(VECTOR_A, MAX, MPI_INT, RECV, 2, MPI_COMM_WORLD, &status);
				MPI_Recv(VECTOR_B, MAX, MPI_INT, RECV, 3, MPI_COMM_WORLD, &status);

				int VECTOR_RES[MAX];

				for(int i = 0; i < MAX; i++)
				{
					VECTOR_RES[i] = (VECTOR_A[i] + VECTOR_B[i]);
				}
				printf("Vector suma : \n");
				imprimirArreglo(VECTOR_RES, MAX);
			}
		}
	}

	MPI_Finalize();
	return EXIT_SUCCESS;
}

void llenarArreglo(int VECTOR[], int MAX)
{
	for(int i = 0; i < MAX; i++)
	{
		VECTOR[i] = (rand()%120) + 1;
	}
}

void imprimirArreglo(int VECTOR[], int MAX)
{
	for(int i = 0; i < MAX; i++)
	{
		printf("%d\n", VECTOR[i]);
	}
}
