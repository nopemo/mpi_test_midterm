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
    
  }
  else
  {

  }

  MPI_Finalize();
  return 0;
}
