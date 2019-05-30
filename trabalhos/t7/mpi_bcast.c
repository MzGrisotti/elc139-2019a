// Adaptado de www.mpitutorial.com
// Exemplo de implementação do MPI_Bcast usando MPI_Send e MPI_Recv

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>


int main(int argc, char** argv) {

  int myrank;    // "rank" do processo
  int p;         // numero de processos
  int root;      // rank do processo root

  // MPI_Init deve ser invocado antes de qualquer outra chamada MPI
  MPI_Init(&argc, &argv);
  // Descobre o "rank" do processo
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  // Descobre o numero de processos
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  int data, data_recieve;     // dado a ser enviado
  root = 0;     // define o rank do root
  // start time
  struct timeval start, end;
  gettimeofday(&start, NULL);
  if (myrank == root) {
    data = 100;  // atribui um valor para ser enviado
    //printf("Processo %d (root) realizando broadcast do dado %d\n", root, data);
    //sr_bcast(&data, 1, MPI_INT, root, MPI_COMM_WORLD);
    MPI_Bcast(&data, 1, MPI_INT, root, MPI_COMM_WORLD);
  } else {
    MPI_Bcast(&data_recieve, 1, MPI_INT, root, MPI_COMM_WORLD);
    //printf("Processo %d recebendo dado %d do processo root\n", myrank, data_recieve);
  }

  MPI_Barrier(MPI_COMM_WORLD);
  // end time
  if (myrank == root){
    gettimeofday(&end, NULL);
    double runtime = end.tv_sec + end.tv_usec / 1000000.0 - start.tv_sec - start.tv_usec / 1000000.0;
    printf("%.4f\n", runtime);
  }

  MPI_Finalize();
  return 0;
}
