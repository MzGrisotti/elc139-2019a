#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
 {
   double *a;
   double *b;
   double c;
   int wsize;
   int repeat;
   int id;
 } dotdata_t;

// Variaveis globais, acessiveis por todas threads
dotdata_t dotdata;

/*
 * Tempo (wallclock) em microssegundos
 */
long wtime()
{
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec*1000000 + t.tv_usec;
}

/*
 * Preenche vetor
 */
void fill(double *a, int size, double value)
{
   int i;
   for (i = 0; i < size; i++) {
      a[i] = value;
   }
}

void dotprod_threads()
{
   #pragma omp parallel shared(dotdata)
   {
     int id_t;//parte que incrementa o numero da thread para o calculo do offset
     #pragma omp critical
     {
       //printf("oi da thread %d, TID = :%d\n", dotdata.id, omp_get_thread_num());
       id_t = dotdata.id;
       dotdata.id++;
     }
     long offset = (long) id_t;
     double *a = dotdata.a;
     double *b = dotdata.b;
     int wsize = dotdata.wsize;
     int start = offset*wsize;
     int end = start + wsize;
     double mysum;
     int i, k;
     //printf("thread: %d tamanho: %d start: %d end: %d\n", id_t, wsize, start, end);
     for (k = 0; k < dotdata.repeat; k++) {
        mysum = 0.0;
        for (i = start; i < end ; i++)  {
           mysum += (a[i] * b[i]);
        }
     }//parte critica da soma
     #pragma omp critical
     {
     dotdata.c += mysum;
     }
   }
}

/*
 * Funcao principal
 */
int main(int argc, char **argv)
{
   int nthreads, wsize, repeat;
   long start_time, end_time;

   if ((argc != 4)) {
      printf("Uso: %s <nthreads> <worksize> <repetitions>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   nthreads = atoi(argv[1]); //numero de threads
   wsize = atoi(argv[2]);  // worksize = tamanho do vetor de cada thread
   repeat = atoi(argv[3]); // numero de repeticoes dos calculos (para aumentar carga)
   omp_set_num_threads(nthreads); //seta o numero de threads de acordo com o argumento

   // Cria vetores
   dotdata.a = (double *) malloc(wsize*nthreads*sizeof(double));
   fill(dotdata.a, wsize*nthreads, 0.01);
   dotdata.b = (double *) malloc(wsize*nthreads*sizeof(double));
   fill(dotdata.b, wsize*nthreads, 1.0);
   dotdata.c = 0.0;
   dotdata.wsize = wsize;
   dotdata.repeat = repeat;
   dotdata.id = 0;

   // Calcula c = a . b em nthreads, medindo o tempo
   start_time = wtime();
   dotprod_threads();
   end_time = wtime();

   // Mostra resultado e estatisticas da execucao
   //printf("%f\n", dotdata.c);
   printf("%ld\n",(long) (end_time - start_time));
   fflush(stdout);

   free(dotdata.a);
   free(dotdata.b);

   return EXIT_SUCCESS;
}
