#include <omp.h>
#include <iostream>

using namespace std;

int determinant(int *matrix[], int size);
void ijMinor(int *matrix[], int *minorMatrix[], int size, int row, int column);

int main() {
	int size;
	cout<< "Cual es el tamanio de la matriz de la cual quieres hallar la determinante:\t";
	cin >> size;

	int **matrix;
	matrix = new int*[size];
	for (int i = 0; i < size; i++)
		matrix[i] = new int[size];

	cout << "\nINgrese valores de la matriz separados por espacios:\n\n";
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			cin >> matrix[i][j];

	cout << "\nLa determinante de la matriz es:\t" << determinant(matrix, size)
			<< endl;

	return 0;
}

void ijMinor(int *matrix[], int *minorMatrix[], int size, int row, int column) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i < row) {
				if (j < column)
					minorMatrix[i][j] = matrix[i][j];
				else if (j == column)
					continue;
				else
					minorMatrix[i][j - 1] = matrix[i][j];
			} else if (i == row)
				continue;
			else {
				if (j < column)
					minorMatrix[i - 1][j] = matrix[i][j];
				else if (j == column)
					continue;
				else
					minorMatrix[i - 1][j - 1] = matrix[i][j];
			}
		}
	}
}

int determinant(int *matrix[], int size) {
	if (size == 1)
		return matrix[0][0];
	else {
		int result = 0, sign = -1;

#pragma omp parallel for default(none) shared(size,matrix,sign) private(j,k)  reduction(+ : result)

		for (int j = 0; j < size; j++) {

			int **minorMatrix;

			minorMatrix = new int*[size - 1];

			for (int k = 0; k < size - 1; k++)
				minorMatrix[k] = new int[size - 1];

			ijMinor(matrix, minorMatrix, size, 0, j);

			sign *= -1;
			result += sign * matrix[0][j] * determinant(minorMatrix, size - 1);
			for (int i = 0; i < size - 1; i++) {
				delete minorMatrix[i];
			}
		}

		return result;
		delete[] matrix;
	}
}
