#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "metricas.h"

/* Define um ponteiro para função de ordenação.

Todas as funções compatíveis recebem:
vetor de inteiros.
quantidade de elementos.
endereço da estrutura de métricas.

O retorno indica:
1 - execução concluída.
0 - falha ou parâmetros inválidos.
*/
typedef int (*FuncaoOrdenacao)(int *, int, Metricas *);

/* Ativa ou desativa a exibição passo a passo.

Parâmetro:
ativo - 1 para exibir o vetor após operações relevantes
ou 0 para executar sem pausas.
*/
void ordenacao_passo_configurar(int ativo);

/* Algoritmos de ordenação disponíveis no projeto. */

// Bubble Sort.
int bubble_sort(int *v, int n, Metricas *m);

// Selection Sort.
int selection_sort(int *v, int n, Metricas *m);

// Insertion Sort.
int insertion_sort(int *v, int n, Metricas *m);

// Merge Sort.
int merge_sort(int *v, int n, Metricas *m);

// Quick Sort.
int quick_sort(int *v, int n, Metricas *m);

#endif
