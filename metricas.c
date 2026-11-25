#include <stdio.h>
#include <string.h>
#include "metricas.h"

/* Zera todos os campos da estrutura de métricas.

O memset preenche toda a memória ocupada pela estrutura
com zero, evitando a inicialização campo por campo.

A verificação impede o acesso a um ponteiro nulo.
*/
void metricas_zerar(Metricas *m) {
    if (m != NULL) {
        memset(m, 0, sizeof(*m));
    }
}

/* Converte a diferença entre dois instantes para milissegundos.

A multiplicação por 1000 converte segundos em milissegundos.
*/
double tempo_milissegundos(double inicio, double fim) { // Retorna a diferença entre os instantes em milissegundos.
    return (fim - inicio) * 1000.0;
}

/* Apresenta os resultados de uma execução individual.

São exibidos o nome do algoritmo, a quantidade de elementos,
o tipo de dados, as comparações, as trocas, as movimentações
e o tempo médio de execução.
*/
void metricas_relatorio(const Metricas *m, int n, const char *tipo) {
    // Impede o acesso aos campos se o ponteiro for nulo.
    if (m == NULL) return;

    printf("\n--- Relatorio de execucao ---\n");
    printf("Algoritmo: %s\n", m->nome);
    printf("Elementos: %d | Dados: %s\n", n, tipo);
    printf("Comparacoes: %lld\n", m->comparacoes);
    printf("Trocas: %lld\n", m->trocas);
    printf("Movimentacoes: %lld\n", m->movimentacoes);
    printf("Tempo medio: %.6f ms\n", m->tempo_ms);
}

/* Apresenta os resultados de vários algoritmos em formato
de tabela, facilitando a comparação de desempenho.

Cada posição do vetor lista contém as métricas de
um algoritmo diferente.
*/
void metricas_tabela(const Metricas *lista, int quantidade, int n, const char *tipo) {
    // Impede a exibição da tabela se não houver resultados.
    if (lista == NULL || quantidade <= 0) return;

    printf("\nComparacao: %d elementos | %s\n", n, tipo);

    // Exibe o cabeçalho da tabela.
    printf("%-12s %14s %12s %16s %14s\n",
           "Algoritmo",
           "Comparacoes",
           "Trocas",
           "Movimentacoes",
           "Tempo (ms)");

    // Percorre o vetor e apresenta as métricas de cada algoritmo.
    for (int i = 0; i < quantidade; i++) {
        printf("%-12s %14lld %12lld %16lld %14.6f\n",
               lista[i].nome,
               lista[i].comparacoes,
               lista[i].trocas,
               lista[i].movimentacoes,
               lista[i].tempo_ms);
    }
}
