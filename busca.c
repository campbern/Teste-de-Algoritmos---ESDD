#include <stddef.h> // Disponibiliza NULL para verificar ponteiros.
#include "busca.h"

/* BUSCA SEQUENCIAL */

/* Percorre o vetor elemento por elemento até encontrar a chave
ou atingir o final do vetor.

Não exige que os dados estejam ordenados.
No pior caso, examina todos os elementos.
O contador registra cada elemento examinado.
*/
int busca_sequencial(const int *v, int n, int chave,
                     long long *iteracoes) { // Retorna o índice encontrado ou -1 se não encontrar.

    // Verifica se o contador foi informado.
    if (iteracoes == NULL) return -1;

    // Reinicia o contador antes da busca.
    *iteracoes = 0;

    // Verifica se o vetor é válido e possui elementos.
    if (v == NULL || n <= 0) return -1;

    for (int i = 0; i < n; i++) {

        // Cada elemento examinado conta como uma iteração.
        (*iteracoes)++;

        // Verifica se o elemento atual corresponde à chave.
        if (v[i] == chave) {
            return i;
        }
    }

    return -1;
}

/* BUSCA BINÁRIA ITERATIVA */

/* Divide o intervalo de busca pela metade a cada tentativa.

Exige que o vetor esteja ordenado em ordem crescente.
O contador registra cada comparação com o elemento central.
*/
int busca_binaria_iterativa(const int *v, int n, int chave,
                            long long *iteracoes) { // Retorna o índice encontrado ou -1 se não encontrar.

    // Verifica se o contador foi informado.
    if (iteracoes == NULL) return -1;

    // Reinicia o contador antes da busca.
    *iteracoes = 0;

    // Verifica se o vetor é válido e possui elementos.
    if (v == NULL || n <= 0) return -1;

    // Define os limites inicial e final do intervalo.
    int ini = 0;
    int fim = n - 1;

    // Continua enquanto houver posições para pesquisar.
    while (ini <= fim) {

        // Calcula o índice central evitando overflow na soma.
        int meio = ini + (fim - ini) / 2;

        // Conta uma tentativa de busca no elemento central.
        (*iteracoes)++;

        if (v[meio] == chave) {
            return meio;
        }

        if (chave < v[meio]) {

            // A chave, se existir, está na metade esquerda.
            fim = meio - 1;

        } else {

            // A chave, se existir, está na metade direita.
            ini = meio + 1;
        }
    }

    return -1;
}

/* BUSCA BINÁRIA RECURSIVA */

/* Executa a busca binária por meio de chamadas recursivas.

Recebe os limites do intervalo e compartilha o contador
entre as chamadas.

É static porque será utilizada somente neste arquivo.
*/
static int busca_binaria_rec(const int *v, int ini, int fim,
                             int chave, long long *iteracoes) { // Retorna o índice encontrado ou -1 se não encontrar.

    // Caso-base: intervalo vazio, sem elementos para pesquisar.
    if (ini > fim) return -1;

    // Calcula o índice central do intervalo.
    int meio = ini + (fim - ini) / 2;

    // Conta a tentativa realizada nesta chamada.
    (*iteracoes)++;

    if (v[meio] == chave) {
        return meio;
    }

    if (chave < v[meio]) {

        // Continua a pesquisa na metade esquerda.
        return busca_binaria_rec(v, ini, meio - 1,
                                 chave, iteracoes);
    }

    // Continua a pesquisa na metade direita.
    return busca_binaria_rec(v, meio + 1, fim,
                             chave, iteracoes);
}

/* Valida os parâmetros, reinicia o contador e inicia
a busca por meio da função auxiliar recursiva.

Os parâmetros ini e fim representam os limites do intervalo.
O índice fim é inclusivo.

Exige que o vetor esteja ordenado em ordem crescente.
*/
int busca_binaria_recursiva(const int *v, int ini, int fim,
                            int chave, long long *iteracoes) { // Retorna o índice encontrado ou -1 se não encontrar.

    // Verifica se o contador foi informado.
    if (iteracoes == NULL) return -1;

    // Reinicia o contador antes da busca.
    *iteracoes = 0;

    // Verifica os limites básicos do intervalo.
    if (v == NULL || ini < 0 || fim < ini) return -1;

    return busca_binaria_rec(v, ini, fim, chave, iteracoes);
}

/* BUSCA POR INTERPOLAÇÃO */

/* Estima a posição da chave com base nos valores
das extremidades do intervalo.

É especialmente adequada para valores distribuídos
de maneira relativamente uniforme.

Exige que o vetor esteja ordenado em ordem crescente.
O contador registra cada posição examinada.
*/
int busca_interpolacao(const int *v, int n, int chave,
                       long long *iteracoes) { // Retorna o índice encontrado ou -1 se não encontrar.

    // Verifica se o contador foi informado.
    if (iteracoes == NULL) return -1;

    // Reinicia o contador antes da busca.
    *iteracoes = 0;

    // Verifica se o vetor é válido e possui elementos.
    if (v == NULL || n <= 0) return -1;

    // Define os limites inicial e final do intervalo.
    int ini = 0;
    int fim = n - 1;

    // Continua enquanto a chave estiver dentro dos limites dos valores existentes.
    while (ini <= fim &&
           chave >= v[ini] &&
           chave <= v[fim]) {

        // Evita divisão por zero quando todos os valores são iguais.
        if (v[ini] == v[fim]) {
            (*iteracoes)++;

            return v[ini] == chave ? ini : -1;
        }

        // Calcula a posição estimada por interpolação.
        // long long reduz o risco de overflow nas operações.
        long long numerador =
            ((long long)chave - v[ini]) * (fim - ini);

        long long denominador =
            (long long)v[fim] - v[ini];

        int pos = ini + (int)(numerador / denominador);

        // Conta a tentativa de examinar a posição estimada.
        (*iteracoes)++;

        if (v[pos] == chave) {
            return pos;
        }

        if (v[pos] < chave) {

            // A chave, se existir, está à direita.
            ini = pos + 1;

        } else {

            // A chave, se existir, está à esquerda.
            fim = pos - 1;
        }
    }

    return -1;
}
