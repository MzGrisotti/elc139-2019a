# T3: Scheduling com OpenMP


## Programação Paralela - ELC139-2019a

**Nome:** Matheus Zorzo Grisotti

**Programa**: [Programa](/trabalhos/t3/OpenMPDemoABC.cpp)

**Resultados**: [Results](/trabalhos/t3/Output)

## Resultados

 - Schedule `static`, com especificação do `chunk`:

 `Schedule (static) with Chunk
 AAAABBBBCCCCDDDDAAAABBBBCCCCDDDDAAAABBBB
 A: 12 B: 12 C: 8 D: 8`

  - Schedule `static`, sem especificação do `chunk`:

 `Schedule (static) without Chunk
 AAAAAAAAAABBBBBBBBBBCCCCCCCCCCDDDDDDDDDD
 A: 10 B: 10 C: 10 D: 10`

 Com `static` a divisão é feita nos índices do for antes de iniciar as repetições, a diferença entre usar chunk é que ao invés de um intervalo contínuo, cada thread pode pegar vários intervalos separados do for.

 - Schedule `dynamic`, com especificação do `chunk`:

```
Schedule (dynamic) with Chunk
 ACDBBACDBACDBADCBDCADCBDACDBCABCCDABCDBD
 A: 8 B: 10 C: 11 D: 11
 ```

 - Schedule `dynamic`, sem especificação do `chunk`:

```
Schedule (dynamic) without Chunk
BCBCABCABABCABBCABBABCABCACBAACBABCABCAB
A: 13 B: 16 C: 11 D: 0
```

 Com `dynamic` é onde existe a maior variação entre execuções, visto que o intervalo não é partilhado sequencialmente entre as threads, mas sim de forma aleatória. Cada thread pode inclusive receber intervalos adjacentes do vetor.

  - Schedule `guided`, com especificação do `chunk`:

```
Schedule (guided) with Chunk
BBBBBBBBBBCCCCCCCCBBBBBBAAAACCCCBBBBAAAA
A: 8 B: 20 C: 12 D: 0
```

  - Schedule `guided`, sem especificação do `chunk`:

```
Schedule (guided) without Chunk
BBBBBBBBBBCCCCCCCCAAAAAABBBBAAACCCBBACBA
A: 11 B: 17 C: 12 D: 0
```

  O método `guided` é semelhante ao `dynamic`, ele também divide o trabalho em chunks que são atribuidos dinamicamente as threads que terminam suas tarefas, porém, a diferença está no tamanho do chunk, que é proporcional ao número de iterações não associadas divido pelo número de threads. Logo, o tamanho dos chunks diminuem conforme são associados.

 - Schedule `runtime`:

```
Schedule (runtime)
BCBCBABCABACBABACBACABCABCCBACCABCCABCAB
A: 12 B: 14 C: 14 D: 0
```

 - Schedule `auto`:

```
Schedule (auto)
AAAAAAAAAABBBBBBBBBBCCCCCCCCCCDDDDDDDDDD
A: 10 B: 10 C: 10 D: 10
```

  O `auto` deixa o sistema operacional decidir o método de escalonamento, geralmente é usado o `static`

 - Sem exclusão mútua:

```
No exclusion
D---A---CADCADC-B--B--B---DB-ACBA-CDAC--
A: 6 B: 5 C: 6 D: 5
```

  ## Referências

- [OpenMP](https://computing.llnl.gov/tutorials/openMP/)  
  Tutorial do Lawrence Livermore National Laboratory (LLNL) sobre OpenMP.

- [Jaka's Corner - OpenMP: For & Scheduling](http://jakascorner.com/blog/2016/06/omp-for-scheduling.html)  
  Material de apoio sobre a cláusula ```schedule``` do OpenMP.
