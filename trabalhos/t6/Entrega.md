# T6: Comunicação coletiva em MPI


## Programação Paralela - ELC139-2019a

**Nome:** Matheus Zorzo Grisotti

**Programa**: [Programa 1](/trabalhos/t6/matrix_mult_Broad.c)

### Parte 1

  Primeiramente o trecho asseguir do programa original era responsável por fazer um broadcast fazendo um send para todos os processos iterando a váriavel i. E depois em cada processo receber os dados usando o comando *MPI_Recv*.
  ```
 if (myrank == 0){
   for (int i = 1; i < nproc; ++i){
     int lFrom = i * SIZE/nproc;
     int lTo = (i+1) * SIZE/nproc;
     //printf("slice log: %d, %d\n", lFrom, lTo);
     // Broadcast B to other process
     MPI_Send(B, SIZE*SIZE, MPI_INT, i, tag_A, MPI_COMM_WORLD);
     // Send "Total of lines" / "Number of process" lines to other process
     MPI_Send(A[lFrom], (lTo - lFrom) * SIZE, MPI_INT, i, tag_B, MPI_COMM_WORLD);
   }
 }else {
   MPI_Recv(B, SIZE*SIZE, MPI_INT, MPI_ANY_SOURCE, tag_A, MPI_COMM_WORLD, &status);
   MPI_Recv(A[from], (to - from)*SIZE, MPI_INT, MPI_ANY_SOURCE, tag_B, MPI_COMM_WORLD, &status);

 }
 ```
 Esse trecho foi substituído por um comando próprio do MPI responsável por broadcast(**MPI_Bcast**) que é usado para mandar a matriz para todos os processos, e por o comando **MPI_Scatter**, que é tipo um broadcast, só que mais seletivo quanto ao conteúdo que será mandado para cada processo.

```
  MPI_Bcast(B, SIZE*SIZE, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter(A[from], (to-from)*SIZE, MPI_INT, A[from], (to-from)*SIZE, MPI_INT, 0, MPI_COMM_WORLD);
```

 O *MPI_Bcast* é responsável por mandar a matriz B do processo 0 para todos os outros processos, que por sua vez, ao invés de precisar do comando para receber os dados como no programa original, utiliza da mesma chamada de função para já receber os dados, pois a função possui na sua declaração ambos os buffers de envio, quanto de recepção.
 No caso do *MPI_Scatter*, é feito um broadcast seletivo, para cada processo é mandado um pedaço diferente da matriz, e do mesmo modo, cada processo recebe os dados pela mesma chamada de função, por ter também buffers de envio e recebimento.

 O trecho abaixo age ainda da mesma forma, juntando todos os dados diferentes de cada processo resultantes da multiplicação das matrizes.
```
MPI_Gather (C[from], SIZE*SIZE/nproc, MPI_INT, C, SIZE*SIZE/nproc, MPI_INT, 0, MPI_COMM_WORLD);
```

### Parte 2
  ## Referências

- [MPI: A Message-Passing Interface Standard](https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf)  
- [A Comprehensive MPI Tutorial Resource](http://mpitutorial.com/)  
- [Exemplos de comunicação](exemplos/)
- [MPI-Broadcast](https://mpitutorial.com/tutorials/mpi-broadcast-and-collective-communication/)
  MPI Broadcast and Collective Communication
- [MPI-Scatter/Gatter](https://mpitutorial.com/tutorials/mpi-scatter-gather-and-allgather/)
  MPI Scatter, Gather, and Allgather
