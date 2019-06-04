# T7: Avaliação de desempenho de programas MPI


## Programação Paralela - ELC139-2019a

**Nome:** Matheus Zorzo Grisotti

**Computador:** Intel(R) Core(TM) i7-7700K CPU @ 4.20GHz (6Gflops) - 16GB RAM 

**Programa**: [Programa 1](/trabalhos/t7/mpi_bcast.c)/[Programa 2](/trabalhos/t7/avg_timed.c)

### Parte 1

  A parte 1 consistiu em editar o [programa original](/trabalhos/t7/sr_bcast.c) para implementar o broadcast entre os processos com a função nativa do MPI, o programa resultante pode ser conferido acima. Posteriormente foi editado novamente o programa original para ser possivel ver o tempo de execução do mesmo, para isso foi implementado uma barreira para que o processo principal não termine antes que todos os outros processos gerados terminem também, a fim de obter um tempo acurado.
  O programa com o cálculo de tempo pode ser visto [aqui](/trabalhos/t7/sr_bcast_timed.c).
  Apartir disso o seguinte gráfico foi gerado, onde podemos ver que o broadcast com send e recieve teve um desempenho melhor.
  
  ![Tempo](/trabalhos/t7/Tempo%20BroadCast%20nativo%20e%20com%20send-Recieve%20(segundos).png)

### Parte 2

![Tempo1](/trabalhos/t7/100.png)
![Tempo2](/trabalhos/t7/200.png)
![Tempo3](/trabalhos/t7/300.png)

  Como podemos ver, foram executadas runs com diferentes tamanhos de vetor, banda, e latência. Os vetores influenciaram no tempo como o previsto, dobrando o tamanho, o tempo dobra, e assim por diante, variando linearmente conforme o tamanho. A banda e a latência eu decidi pior em um fator de 5 vezes, dividindo em 5 vezes a banda e aumentando em 5 vezes a latência, e conforme mostra o gráfico, a banda teve o maior impacto, piorando quase que no mesmo grau quanto a divisão de banda. Ainda foi feito um teste com a junção dois dois, piorando a banda e a latência, e assim pudemos concluir mais uma vez que a latência(nesse caso), não teve um inpacto muito grande.
 
  OBS: Para capturar o tempo de execução foram usados o método já implementando no código [original](/trabalhos/t7/avg.c) e só descomentadas no [novo](/trabalhos/t7/avg_timed.c)
  
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
