#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);


	#define  LEN   1000

	float val[LEN];
	int count;
	int myrank, minrank, minindex;
	float minval;
	struct {
		float value;
		int   index;
	} in, out;


	in.value = val[0];
	in.index = 0;
	for (i=1; i < count; i++)
		if (in.value > val[i]) {
			in.value = val[i];
			in.index = i;
		}


	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	in.index = myrank*LEN + in.index;
	MPI_Reduce( in, out, 1, MPI_FLOAT_INT, MPI_MINLOC, root, comm );
	if (myrank == root) {
		minval = out.value;
		minrank = out.index / LEN;
		minindex = out.index % LEN;
	}


    MPI_Finalize();

    return EXIT_SUCCESS;
}
