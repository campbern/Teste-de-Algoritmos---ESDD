# Testes de Algoritmos e Estruturas de Dados

Projeto individual desenvolvido em linguagem C, executado pelo terminal, com o objetivo de implementar, testar e comparar algoritmos de ordenação, algoritmos de busca e estruturas de dados.

## Funcionalidades

### Vetores

- Geração de vetores aleatórios, ordenados e invertidos.
- Exibição e cópia de vetores.
- Verificação da ordenação dos elementos.
- Preservação do vetor-base: os algoritmos de ordenação trabalham sobre cópias, sem modificar o conjunto original.

### Algoritmos de ordenação

- Bubble Sort.
- Selection Sort.
- Insertion Sort.
- Merge Sort.
- Quick Sort.
- Execução individual dos algoritmos.
- Comparação dos cinco algoritmos.
- Modo passo a passo para ordenações individuais com até 20 elementos.

### Algoritmos de busca

- Busca sequencial.
- Busca binária iterativa.
- Busca binária recursiva.
- Busca por interpolação.

As buscas binárias e por interpolação exigem um vetor previamente ordenado em ordem crescente. O programa verifica essa condição antes de executar essas buscas.

### Estruturas de dados

- Lista simplesmente encadeada.
- Pilha implementada com vetor dinâmico.
- Fila circular implementada com vetor dinâmico.
- Árvore binária de busca.
- Tabela hash com encadeamento separado.

O programa constrói as cinco estruturas a partir dos elementos do vetor-base, exibe seus conteúdos e permite realizar consultas na lista, na árvore binária de busca e na tabela hash.

Também demonstra a remoção de elementos da pilha e da fila.

### Métricas

- Contagem de comparações.
- Contagem de trocas.
- Contagem de movimentações.
- Contagem de iterações nas buscas.
- Medição de tempo com `clock()`.
- Média de cinco execuções nas ordenações realizadas sem o modo passo a passo.
- Uma execução individual no modo passo a passo.

## Estrutura do projeto

- main.c 
Menu principal e integração dos módulos.
- vetor.c / vetor.h
Criação, geração, cópia, impressão e validação de vetores.
- ordenacao.c / ordenacao.h
Implementação dos cinco algoritmos de ordenação.
- busca.c / busca.h
Implementação dos quatro algoritmos de busca.
- estruturas.c / estruturas.h
Implementação das cinco estruturas de dados.
- metricas.c / metricas.h
Registro, cálculo e apresentação das métricas dos algoritmos.
- Makefile
Automatização do processo de compilação do projeto.

## Compilação

O projeto foi compilado no Windows, utilizando o ambiente MSYS2 UCRT64 e o compilador GCC.

A compilação principal foi realizada por meio do Makefile, com o comando:

```bash
make
```

Também foi verificada a possibilidade de compilação direta pelo GCC, sem utilização do Makefile, por meio do seguinte comando:

```bash
gcc -Wall -Wextra -pedantic -O2 main.c vetor.c ordenacao.c busca.c metricas.c estruturas.c -o testes_estruturas.exe
```

Após a compilação, o executável `testes_estruturas.exe` foi executado pelo terminal para a realização dos testes funcionais.

A limpeza dos arquivos gerados durante a compilação foi realizada por meio do comando:

```bash
make clean
```

## Testes realizados

Foram realizados testes funcionais manuais pelo terminal, contemplando as seguintes funcionalidades:

- Criação e exibição de conjuntos de dados.
- Execução individual dos cinco algoritmos de ordenação.
- Execução do modo passo a passo.
- Comparação dos algoritmos por meio de tabela de métricas.
- Busca de valores existentes e inexistentes.
- Construção e exibição das cinco estruturas de dados.
- Consultas na lista simplesmente encadeada, na árvore binária de busca e na tabela hash.
- Remoção de elementos da pilha e da fila.
- Encerramento do programa.

### Resultados observados

- Ordenações: os cinco algoritmos ordenaram corretamente os conjuntos utilizados nos testes.
- Buscas: os algoritmos localizaram corretamente o valor 5 na posição 4 de um vetor ordenado de 1 a 10. Também identificaram corretamente valores inexistentes, como 0 e 11.
- Estruturas: as cinco estruturas foram construídas a partir do vetor-base e exibidas. As consultas realizadas apresentaram os resultados esperados.
- Pilha e fila: as remoções retornaram, respectivamente, os valores 10 e 1, conforme os princípios LIFO (Last In, First Out) e FIFO (First In, First Out).
- Encerramento: o programa foi finalizado corretamente pelo menu principal.

## Observações

- A tabela hash utiliza encadeamento separado e capacidade fixa de 101 posições.
- A árvore binária de busca não insere valores duplicados.
- A lista simplesmente encadeada permite valores repetidos.
- A árvore binária de busca não possui balanceamento automático.
- O tempo de execução depende das características da máquina e pode ser muito pequeno para conjuntos reduzidos.
- Os testes realizados não representam uma validação exaustiva de todas as entradas possíveis.

## Melhorias futuras

- [ ] Implementar geração automática de dependências entre arquivos `.c` e `.h` no Makefile, utilizando `-MMD` e `-MP`.
- [ ] Ampliar a validação das entradas fornecidas pelo usuário.
- [ ] Avaliar a implementação de uma árvore binária de busca balanceada.
- [ ] Ampliar os testes com diferentes tamanhos e configurações de vetores.