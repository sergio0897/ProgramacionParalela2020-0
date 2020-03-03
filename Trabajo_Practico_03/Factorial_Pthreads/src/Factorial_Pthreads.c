
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5

pthread_mutex_t signalLock;




void * factorial(int n) {
	int result;

	if (n == 0 || n == 1) {
		result = 1;
	} else {
		int i;
		int array[n];
		array[0] = 1;
		array[1] = 1;

		for (i = 2; i <= n; i++) {
			array[i] = array[i - 1] * i;
		}
		result = array[n];
	}

	pthread_mutex_lock(&signalLock);
	printf("respuesta: %d\n", result);
	pthread_mutex_unlock(&signalLock);

	pthread_exit(0);
}





int main(void) {
	pthread_t id[N];
	int i, j;
	void * ret;

	for (i = 0; i < N; i++) {
		j = i + 2;
		printf("pregunta: %d\n", j);
		pthread_create(&id[i], NULL, factorial, j);
	}

	for (i = 0; i < N; i++) {
		pthread_join(id[i], &ret);
	}

	return 0;
}
