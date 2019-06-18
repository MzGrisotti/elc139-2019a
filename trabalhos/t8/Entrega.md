# T8: Geração de Imagem em Paralelo com CUDA


## Programação Paralela - ELC139-2019a

**Nome:** Matheus Zorzo Grisotti

**Computador:** ![Testa](/trabalhos/t8/tesla.png)

**Programa**: [Programa 1](/trabalhos/t8/wavecuda1.cu)/[Programa 2](/trabalhos/t8/wavecuda2.cu)

### Parte 1

A Legenda no Eixo X mostra os casos de teste na forma de Frames/Width. No caso do programa 1, o número de frames é igual ao número de threads, então pode se observar que, como a gpu disponibiliza de 2500+ núcleos, o speedup vai aumentar ainda mais conforme aumenta o número de frames, até chegar no limite de threads disponíveis. O aumento do tempo ocorre de forma linear, dobrando a carga, dobrasse o tempo.
![wave1](/trabalhos/t8/wave1.png)

### Parte 2
