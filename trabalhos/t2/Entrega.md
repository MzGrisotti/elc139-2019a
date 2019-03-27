[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > Trabalhos

# T2: Programação Paralela Multithread


## Programação Paralela - ELC139-2019a

## Matheus Zorzo Grisotti

### Questões Pthreads

#### 1. Explique como se encontram implementadas as 4 etapas de projeto: particionamento, comunicação, aglomeração, mapeamento (use trechos de código para ilustrar a explicação).

##### Particionamento


O Particionamento é a quebra de um problema maior em problemas menores que permitam o programa ser executado em paralelo. Nesse trecho abaixo é calculado o vetor de carga baseado no número de threads usadas:

```
dotdata.a = (double *) malloc(wsize*nthreads*sizeof(double));
fill(dotdata.a, wsize*nthreads, 0.01);
dotdata.b = (double *) malloc(wsize*nthreads*sizeof(double));
fill(dotdata.b, wsize*nthreads, 1.0);
```

Depois, esse pŕoximo trecho de código balancea a carga desses vetores para serem executados por multiplas threads:

```
int i, k;
long offset = (long) arg;
double *a = dotdata.a;
double *b = dotdata.b;     
int wsize = dotdata.wsize;
int start = offset*wsize;
int end = start + wsize;
double mysum;

for (k = 0; k < dotdata.repeat; k++) {
   mysum = 0.0;
   for (i = start; i < end ; i++)  {
      mysum += (a[i] * b[i]);
   }
}
```
##### Comunicação

A parte de comunicação é onde as dependências são resolvidas, ou seja, é a parte crítica do código onde somente uma thread pode acessar por vez, e ela acontece no trecho abaixo:

```
pthread_mutex_lock (&mutexsum);
dotdata.c += mysum;
pthread_mutex_unlock (&mutexsum);
```
##### Aglomeração

A aglomeração é onde os resultados de cada thread são juntados em uma variável em comum, e é feita de um modo onde tenha o maior tempo possível de processamento e o menor possível de comunicação, para não manter a thread ociosa.

```
//processamento

for (k = 0; k < dotdata.repeat; k++) {
   mysum = 0.0;
   for (i = start; i < end ; i++)  {
      mysum += (a[i] * b[i]);
   }
}

//comunicação

pthread_mutex_lock (&mutexsum);
dotdata.c += mysum;
pthread_mutex_unlock (&mutexsum);
```
##### Mapeamento

É a distribuição das pequenas tarefas da etapa de particionamento para cada thread de forma balanceada, e está descrita no código abaixo:

```
threads = (pthread_t *) malloc(nthreads * sizeof(pthread_t));
pthread_mutex_init(&mutexsum, NULL);

pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
//Aqui é distribuida as tarefas para cada thread
for (i = 0; i < nthreads; i++) {
   pthread_create(&threads[i], &attr, dotprod_worker, (void *) i);
}
```
#### 2. Considerando o tempo (em microssegundos) mostrado na saída do programa, qual foi a aceleração (speedup) com o uso de threads?

Foi feito 5 execuções e tirado a média, 4099322 usec para 1 thread e 2078058 usec para 2.

Speedup = TSeq / TPar

O Speedup foi de 1,97 aproximadamente.

#### 3. A aceleração  se sustenta para outros tamanhos de vetores, números de threads e repetições? Para responder a essa questão, você terá que realizar diversas execuções, variando o tamanho do problema (tamanho dos vetores e número de repetições) e o número de threads (1, 2, 4, 8..., dependendo do número de núcleos). Cada caso deve ser executado várias vezes, para depois calcular-se um tempo de processamento médio para cada caso. Atenção aos fatores que podem interferir na confiabilidade da medição: uso compartilhado do computador, tempos muito pequenos, etc.

Como o código calcula a carga do programa de acordo com o tamanho do vetor, as repetições e o número de threads usadas, foi feito a medição do tempo em 3 cargas distintas, 2 bilhões, 500 milhões, e 100 milhões. Para isso foi ajustado o número de repetições a fim de manter a mesma carga para todas as execuções de diferentes números de threads. Foi feito 20 execuções para cada linha de cada tabela usando um programa [bash](/trabalhos/t2/pthreads_dotprod/Bash) que armazenava a saída do programa(o tempo de execução) em um arquivo txt, que por sua vez foi examinado para retirar números fora da curva e então usado para gerar o arquivo [results.csv](/trabalhos/t2/results.csv) e calcular as médias mostradas abaixo:

#### Carga de 2.000.000.000

| Modo      | Vetor   | Repetições | Tempo(usec) |
|-----------|---------|------------|-------|
| 1 Threads | 1000000 | 2000       |  4180914     |
| 2 Threads | 1000000 | 1000       |  2087966     |
| 4 Threads | 1000000 | 500        |  1099401     |
| 8 Threads | 1000000 | 250        |   987926    |

#### Carga de 500.000.000

| Modo      | Vetor  | Repetições | Tempo(usec)  |
|-----------|--------|------------|-------|
| 1 Threads | 250000 | 2000       | 1042402      |
| 2 Threads | 250000 | 1000       |  517028     |
| 4 Threads | 250000 | 500        |   276977    |
| 8 Threads | 250000 | 250        |   220160    |

#### Carga de 100.000.000

| Modo      | Vetor | Repetições | Tempo(usec)  |
|-----------|-------|------------|-------|
| 1 Threads | 50000 | 2000       |   207277    |
| 2 Threads | 50000 | 1000       |   103051    |
| 4 Threads | 50000 | 500        |    62501   |
| 8 Threads | 50000 | 250        |    43148   |


#### 4. Elabore um gráfico/tabela de aceleração a partir dos dados obtidos no exercício anterior.

![Speedup](/trabalhos/t2/graph.png)

Como é possível observar, existe um salto de desempenho muito significativo de 1 para 2 threads, e de 2 para 4 threads, que se mantém ao longo de todos os testes nas diversas mudanças nos fatores(tamanho do vetor e repetições). Por outro lado, o pulo de 4 para 8 threads é menos constante, dependendo dos fatores e da carga do programa, nos testes de 2 bilhões(de carga) o salto foi muito pequeno, porém, onde houve um volume pequeno de dados e repetições o salto se mostrou significativo.

#### 5. Explique as diferenças entre [pthreads_dotprod.c](pthreads_dotprod/pthreads_dotprod.c) e [pthreads_dotprod2.c](pthreads_dotprod/pthreads_dotprod2.c). Com as linhas removidas, o programa está correto?

A diferença entre os dois arquivos é que o [pthreads_dotprod.c](pthreads_dotprod/pthreads_dotprod.c) implementa um semáforo mutex, enquanto o [pthreads_dotprod2.c](pthreads_dotprod/pthreads_dotprod2.c) não, isso implica em um possível erro devido ao acesso liberado a qualquer thread a qualquer hora à variável "dotdata.c", podendo gerar um erro na somatória final, pois se uma thread realizar a soma enquanto outra também está somando, a variável vai ser sobrescrita e somente a conta de uma das threads tera sido corretamente computada.

## Parte II: OpenMP


1. Nesta parte você vai trabalhar com um programa muito simples que usa OpenMP: [ompsimple.c](openmp/ompsimple.c).

2. Compile o programa usando a flag `-fopenmp`, que habilita OpenMP:

   ```
   gcc -fopenmp -o ompsimple ompsimple.c
   ```

3. Execute o programa com 8 threads:

   ```
   OMP_NUM_THREADS=8 ./ompsimple
   ```

### Implementação OpenMP

1. Implemente um programa equivalente a [pthreads_dotprod.c](pthreads_dotprod/pthreads_dotprod.c) usando OpenMP.

2. Avalie o desempenho do programa em OpenMP, usando os mesmos dados/argumentos do programa com threads POSIX.

A tabela abaixo contém os fatores que foram usados para os testes, assim como o seu tempo resultante em microssegundos do programa em OpenMP, e também foi adicionado uma coluna da tabela anterior que contém o tempo do programa de Pthreads para fins comparativos.

#### Carga de 2.000.000.000

| Modo      | Vetor   | Repetições | OpenMP | Pthread(usec) |
|-----------|---------|------------|----------|--------------|
| 1 Threads | 1000000 | 2000       |   4135093       |  4180914     |
| 2 Threads | 1000000 | 1000       |   2103837       |  2087966     |
| 4 Threads | 1000000 | 500        |    1110572      |  1099401     |
| 8 Threads | 1000000 | 250        |    1031730      |   987926    |

#### Carga de 500.000.000

| Modo      | Vetor  | Repetições | OpenMP | Tempo(usec)  |
|-----------|--------|------------|----------|---------|
| 1 Threads | 250000 | 2000       |  1024650        |1042402      |
| 2 Threads | 250000 | 1000       |   520031        | 517028     |
| 4 Threads | 250000 | 500        |   266166        |  276977    |
| 8 Threads | 250000 | 250        |    240441       |  220160    |

#### Carga de 100.000.000

| Modo      | Vetor | Repetições | OpenMP | Tempo(usec)  |
|-----------|-------|------------|--------|-------------|
| 1 Threads | 50000 | 2000       |  204532      |   207277    |
| 2 Threads | 50000 | 1000       |   103369       |   103051    |
| 4 Threads | 50000 | 500        |   52095     |    62501   |
| 8 Threads | 50000 | 250        |    42407     |    43148   |

Abaixo está a comparação entre os speedups observados para ambos os programas.

![Speedup_Comp](/trabalhos/t2/graph_2.png)

## Material de apoio

- [POSIX Threads Programming](http://www.llnl.gov/computing/tutorials/pthreads/)  
  Tutorial do Lawrence Livermore National Laboratory (LLNL) sobre Pthreads.

- [Tutorial OpenMP](https://computing.llnl.gov/tutorials/openMP/)  
  Tutorial do Lawrence Livermore National Laboratory (LLNL) sobre OpenMP.
