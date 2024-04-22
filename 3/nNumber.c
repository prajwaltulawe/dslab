#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define n 10

int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

int main(int argc, char *argv[]) {
  int pid, np;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  int element_per_process = n / np;
  int sum = 0;
  int start_index = pid * element_per_process;
  int end_index = (pid + 1) * element_per_process;
  if (pid == np - 1) end_index = n;

  for (int i = start_index; i < end_index; i++) {
    sum += a[i];
  }

  if (pid != 0) {
    MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  } else {
    int temp;
    for (int i = 1; i < np; i++) {
      MPI_Recv(&temp, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);

      sum += temp;
    }
    printf("Sum of array is %d \n", sum);
  }

  MPI_Finalize();
  return 0;
}

/*
Terminal 1:
mpicc nNumber.c -o obj
mpirun -np 2 ./obj
*/