#ifndef METRICAS_H
#define METRICAS_H

/* Estrutura responsável por armazenar os resultados
obtidos durante a execução de um algoritmo.

Os campos permitem comparar o desempenho dos
algoritmos de ordenação.
*/
typedef struct {
    char nome[30];              // Nome do algoritmo.
    long long comparacoes;      // Quantidade de comparações realizadas.
    long long trocas;           // Quantidade de trocas entre elementos.
    long long movimentacoes;    // Quantidade de movimentações de elementos.
    double tempo_ms;            // Tempo de execução em milissegundos.
} Metricas;

/* Inicializa todas as métricas com zero.

Parâmetro:
m - endereço da estrutura que será zerada.
*/
void metricas_zerar(Metricas *m);

/* Converte um intervalo de tempo para milissegundos.

Parâmetros:
inicio - instante inicial.
fim - instante final.
*/
double tempo_milissegundos(double inicio, double fim); // Retorna a diferença entre os instantes em milissegundos.

/* Exibe um relatório individual de execução.

Parâmetros:
m - métricas do algoritmo.
n - quantidade de elementos processados.
tipo - tipo de organização dos dados.
*/
void metricas_relatorio(const Metricas *m, int n, const char *tipo);

/* Exibe uma tabela para comparar os resultados
de diferentes algoritmos.

Parâmetros:
lista - vetor contendo as métricas.
quantidade - número de resultados armazenados.
n - quantidade de elementos processados.
tipo - tipo de organização dos dados.
*/
void metricas_tabela(const Metricas *lista, int quantidade, int n, const char *tipo);

#endif
