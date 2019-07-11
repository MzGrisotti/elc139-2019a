[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2018a) > T10

## Nome: Ricardo Kunde Schlesner e Matheus Zorzo Grisotti

### [main_paralel.cu](https://github.com/kadykunde/elc139-2019a/blob/master/trabalhos/t10/main_paralel.cu)
### [main_cpp (sequencial)](https://github.com/kadykunde/elc139-2019a/blob/master/trabalhos/t10/main_cpp.cpp)

### Ideia do Programa

Nós decidimos incorporar o que aprendemos em computação gráfica junto com os conhecimentos de programação paralela, o programa gera uma ou mais imagens (dependendo do número de frames especificados) de um cubo 3d formado por pontos girando. Por ser um cubo 3d, existe muitos laços de 3 níveis no código, e vimos oportunidade de paralelisação nisso.

Estamos utilizando CUDA, e isso nos da acesso a um alto número de threads,então decidimos implementar a paralelização criação de cada frame, e não separa-los por frames, pois então a paralelização teria efeito idependente da quantia de frames, além de ser mais facil implementação.

<img src="https://i.imgur.com/rfG77QU.gif">

### Desempenho

A seguir segue graficos com o tempo de execução e speedup para diferentes quantias de frames, para um cubo 100x100x100.

<img src="https://cdn.discordapp.com/attachments/434506399200837633/598687210677469209/Sequencial_x_Cuda.png" width="600">


<img src="https://cdn.discordapp.com/attachments/434506399200837633/598687884710510592/Frames_e_Speedup.png" width="600">


