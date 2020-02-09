#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);


    double ain[30], aout[30];
      int  ind[30];
      struct {
          double val;
          int   rank;
      } in[30], out[30];
      int i, miRango, root;

      MPI_Comm_rank(MPI_COMM_WORLD, &miRango);
      for (i=0; i<30; ++i) {
             in[i].val = ain[i];
             in[i].rank = miRango;
         }
         MPI_Reduce( in, out, 30, MPI_DOUBLE_INT, MPI_MAXLOC, root, comm );
         if (miRango == root) {
             for (i=0; i<30; ++i) {
                 aout[i] = out[i].val;
                 ind[i] = out[i].rank;
             }
         }



    MPI_Finalize();

    return EXIT_SUCCESS;
}
