// This is the program for calculating the multiplication of two matrices

#include <iostream>
#include <unistd.h>
#include <mpi.h>
#include <matrix.h>

int main(int argc, char *argv[])
{
  MPI_Init(&argc, &argv);
  int rank = 0;
  int size = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  char hostname[256];
  for (int i = 0; i < size; ++i)
  {
    if (i == rank)
    {
      gethostname(hostname, sizeof(hostname));
      std::cout << "rank=" << i << " ,hostname = " << hostname << std::endl;
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }

  // check if the program is the leader or the child
  bool isLeader = (rank == 0);

  // if the program is the leader, then it will read the matrix from the file
  // if the program is the child, then it will wait and receive the matrix from the leader
  Matrix matrixA;
  Matrix matrixB;
  Matrix matrixResult;
  if (isLeader)
  {
    matrixA = *load_matrix("matrixA.txt");
    matrixB = *load_matrix("matrixB.txt");
    matrixResult = *create_matrix(matrixA.max_row, matrixB.max_col);

    for (int i; i <= size - 1; i++)
    {
      MPI_Send(&matrixA, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(&matrixB, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(&matrixResult, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }

    // wait for the result from the child
    for (int i; i <= size - 1; i++)
    {
      MPI_Recv(&matrixResult, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    save_matrix(&matrixResult, "matrixResult.txt");
  }
  else
  {
    // this is the child
    MPI_Recv(&matrixA, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&matrixB, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&matrixResult, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // determine the number of rows that the child will calculate
    for (int i; i <= matrixA.max_row; i++)
    {
      if (i % (size - 1) == rank - 1)
      {
        for (int j; j <= matrixB.max_col; j++)
        {
          double sum = 0;
          for (int k; k <= matrixA.max_col; k++)
          {
            sum += get_matrix(&matrixA, i, k) * get_matrix(&matrixB, k, j);
          }
          set_matrix(&matrixResult, i, j, sum);
        }
      }
    }
    MPI_Send(&matrixResult, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }
  MPI_Finalize();
  return 0;
}
