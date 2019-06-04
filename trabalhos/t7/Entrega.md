# T7: Avaliação de desempenho de programas MPI


## Programação Paralela - ELC139-2019a

**Nome:** Matheus Zorzo Grisotti

**Programa**: [Programa](/trabalhos/t7/mpi_bcast.c)

### Parte 1

  A parte 1 consistiu em editar o [programa original](/trabalhos/t7/sr_bcast.c) para implementar o broadcast entre os processos com a função nativa do MPI, o programa resultante pode ser conferido acima. Posteriormente foi editado novamente o programa original para ser possivel ver o tempo de execução do mesmo, para isso foi implementado uma barreira para que o processo principal não termine antes que todos os outros processos gerados terminem também, a fim de obter um tempo acurado.
  O programa com o cálculo de tempo pode ser visto [aqui](/trabalhos/t7/sr_bcast_timed.c).
  Apartir disso o seguinte gráfico foi gerado, onde podemos ver que o broadcast com send e recieve teve um desempenho melhor.
  
  ![Tempo](/trabalhos/t7/Tempo%20BroadCast%20nativo%20e%20com%20send-Recieve%20(segundos).png)

### Parte 2

![Tempo1](/trabalhos/t7/100.png)
![Tempo2](/trabalhos/t7/200.png)
![Tempo3](/trabalhos/t7/300.png)

## Referências

- [MPI: A Message-Passing Interface Standard](https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf)  
- [A Comprehensive MPI Tutorial Resource](http://mpitutorial.com/)  
- [Exemplos de comunicação](exemplos/)
- [MPI-Broadcast](https://mpitutorial.com/tutorials/mpi-broadcast-and-collective-communication/)
  MPI Broadcast and Collective Communication
- [MPI-Scatter/Gatter](https://mpitutorial.com/tutorials/mpi-scatter-gather-and-allgather/)
  MPI Scatter, Gather, and Allgather
- [SIMGRID](http://simgrid.gforge.inria.fr/simgrid/3.20/doc/getting_started.html)
  SMPI
