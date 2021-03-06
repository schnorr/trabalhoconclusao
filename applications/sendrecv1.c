/* 
 * sendrecv1.c
 * MPI_Send and MPI_Recv
 * The processes send and receive messages to/from its neighboors.
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(num_procs < 2 || num_procs % 2 != 0) {
      MPI_Finalize();
      return 1;
    }

    int i;
    for (i = 0; i < 10; i++)
    if(rank % 2 == 0) {
      int *msg = malloc(100*sizeof(int));
      MPI_Send(&msg, 100, MPI_INT, rank + 1, 1234, MPI_COMM_WORLD);
      printf("process %d sent message to process %d\n", rank, rank + 1);
    }
    else {
      MPI_Status status;
      int buffer[100];
      MPI_Recv(&buffer, 100, MPI_INT, rank - 1, 1234, MPI_COMM_WORLD, &status);
      printf("process %d received a message from process %d\n", rank, rank - 1);
    }
    MPI_Finalize();
}
