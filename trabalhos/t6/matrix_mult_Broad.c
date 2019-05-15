
#include <mpi.h>
#include <stdio.h>

#define SIZE 8      /* Size of matrices */

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];


void fill_matrix(int m[SIZE][SIZE])
{
  static int n=0;
  int i, j;
  for (i=0; i<SIZE; i++)
    for (j=0; j<SIZE; j++)
      m[i][j] = n++;
}

void print_matrix(int m[SIZE][SIZE])
{
  int i, j = 0;
  for (i=0; i<SIZE; i++) {
    printf("\n\t| ");
    for (j=0; j<SIZE; j++)
      printf("%*d", 6, m[i][j]);
    printf("|");
  }
}


int main(int argc, char *argv[])
{
   int myrank, nproc, from, to, i, j, k;
   MPI_Status status;
  
   MPI_Init (&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &myrank); /* who am i */
   MPI_Comm_size(MPI_COMM_WORLD, &nproc); /* number of processors */

   if (SIZE%nproc!=0) {
     if (myrank==0) printf("Matrix size not divisible by number of processors\n");
     MPI_Finalize();
     return -1;
   }

   from = myrank * SIZE/nproc;
   to = (myrank+1) * SIZE/nproc;

   /* Process 0 fills the input matrices and broadcasts them to the rest */

   if (myrank==0) {
     fill_matrix(A);
     fill_matrix(B);
   }

   //Faz o broadcast da matriz B do processo 0 para todos os processos
   //todos os processos que nao são o 0 recebem os argumentos por esse comando
   MPI_Bcast(B, SIZE*SIZE, MPI_INT, 0, MPI_COMM_WORLD);
   //Faz a separação da matriz A para cada processo
   //cada processo recebe um pedaço de tamanho (to-from) da matriz A para multiplicar pela matriz B
   MPI_Scatter(A[from], (to-from)*SIZE, MPI_INT, A[from], (to-from)*SIZE, MPI_INT, 0, MPI_COMM_WORLD);


   printf("computing slice %d (from row %d to %d)\n", myrank, from, to-1);
   for (i=from; i<to; i++) {
     for (j=0; j<SIZE; j++) {
       C[i][j]=0;
       for (k=0; k<SIZE; k++){
         C[i][j] += A[i][k]*B[k][j];
       }
     }
   }

   //Junta todos os pedaços da matriz C dos processos no processo 0
   MPI_Gather (C[from], SIZE*SIZE/nproc, MPI_INT, C[from], SIZE*SIZE/nproc, MPI_INT, 0, MPI_COMM_WORLD);


   if (myrank==0) {
     printf("\n\n");
     print_matrix(A);
     printf("\n\n\t       * \n");
     print_matrix(B);
     printf("\n\n\t       = \n");
     print_matrix(C);
     printf("\n\n");
   }

   MPI_Finalize();
   return 0;
}



