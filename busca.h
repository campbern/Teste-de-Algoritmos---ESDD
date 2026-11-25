#ifndef BUSCA_H
#define BUSCA_H

/* Percorre o vetor desde o primeiro elemento até encontrar
a chave ou chegar ao final.

Não exige que o vetor esteja ordenado.
*/
int busca_sequencial(const int *v, int n, int chave,
                     long long *iteracoes); // Retorna o índice encontrado ou -1 se não encontrar.

/* Reduz progressivamente o intervalo de busca pela metade.

Requer vetor previamente ordenado em ordem crescente.
*/
int busca_binaria_iterativa(const int *v, int n, int chave,
                            long long *iteracoes); // Retorna o índice encontrado ou -1 se não encontrar.

/* Realiza a busca binária por meio de chamadas recursivas.

Os parâmetros ini e fim representam os limites do intervalo.
O índice fim é inclusivo.

Requer vetor previamente ordenado em ordem crescente.
*/
int busca_binaria_recursiva(const int *v, int ini, int fim,
                            int chave, long long *iteracoes); // Retorna o índice encontrado ou -1 se não encontrar.

/* Estima a posição da chave considerando os valores
existentes nas extremidades do intervalo.

É mais adequada para valores distribuídos de maneira uniforme.
Requer vetor previamente ordenado em ordem crescente.
*/
int busca_interpolacao(const int *v, int n, int chave,
                       long long *iteracoes); // Retorna o índice encontrado ou -1 se não encontrar.

#endif
