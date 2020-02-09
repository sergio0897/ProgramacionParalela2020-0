/*
 ============================================================================
 Name        : Solucionario_PC.c
 Author      : Sergio de la Torre
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */

//PREGUNTA 6

#include <math.h> 
#include "mpi.h" 
#include <iostream>

using namespace std;

void imprimirVector(int m[], int n, char nombre[]);
 
int main(int argc, char *argv[]) {

	int n = 8;
	int x;
	int rank;
	int size;
	int acu_total = 0;
	int nro_veces = 0;
	int send_n;

	bool resultImprimir = true;

	int *local_A;
	int A[n]={4, 5, 5, 8, 6, 0, 6, 3};

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank==0) imprimirVector(A, n, "Vector");

	if(n%size == 0)
	{
		send_n = n / size;
		local_A = new int[send_n];

		MPI_Scatter(A, send_n, MPI_INT, local_A, send_n, MPI_INT, 0, MPI_COMM_WORLD);
			if(rank == 0){
					printf("Ingrese un número -> ");
					cin>>x;
			}

		MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);
		for(int i = 0; i<send_n; i++){
			if(local_A[i] == x){
				acu_total++;
			}
		}

		MPI_Reduce(&acu_total, &nro_veces, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	}
	else
	{
		resultImprimir = false;
	}

	if(rank == 0)
	{
		if(!resultImprimir)
		{
			printf("La cantidad de procesos \"%d\" debe ser múltiplo de la cantidad de elementos del arreglo\n", size);
		}
		else
		{
			printf("El numero %d se repite %d veces\n", x, nro_veces);
		}
	}

	MPI_Finalize();
	return 0;
}

void imprimirVector(int m[], int n, char nombre[]){
	printf("%s: [", nombre);
	for (int l = 0; l < n; l++)
	printf("%d ", m[l]);
	printf("]\n");
}

