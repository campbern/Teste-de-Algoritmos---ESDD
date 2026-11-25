#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "vetor.h"

/* CRIAÇÃO DINÂMICA DO VETOR */

/* Reserva espaço na memória para armazenar n inteiros.

malloc() solicita memória dinamicamente.
O espaço reservado permanece disponível até que
seja liberado com free().

A verificação com SIZE_MAX evita que o cálculo
do tamanho da alocação ultrapasse o limite de size_t.
*/
int *vetor_criar(int n) { // Retorna o endereço da memória alocada ou NULL se os parâmetros forem inválidos ou a alocação falhar.

    // Não permite vetores com quantidade inválida.
    if (n <= 0 || (size_t)n > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    // Reserva memória conforme a quantidade e o tamanho dos elementos.
    return malloc((size_t)n * sizeof(int));
}

/* GERAÇÃO DOS DADOS */

/* Preenche o vetor conforme o tipo selecionado.

DADOS_ALEATORIOS:
Gera valores aleatórios entre 0 e 9999.

DADOS_ORDENADOS:
Preenche o vetor em ordem crescente.

DADOS_INVERTIDOS:
Preenche o vetor em ordem decrescente.
*/
void vetor_gerar(int *v, int n, TipoDados tipo) {

    // Verifica se o ponteiro é válido e se a quantidade de elementos é positiva.
    if (v == NULL || n <= 0) return;

    // Percorre todas as posições do vetor.
    for (int i = 0; i < n; i++) {

        // Gera dados em ordem crescente.
        if (tipo == DADOS_ORDENADOS) {
            v[i] = i + 1;
        }

        // Gera dados em ordem decrescente.
        else if (tipo == DADOS_INVERTIDOS) {
            v[i] = n - i;
        }

        // Para qualquer outro tipo, gera valores aleatórios.
        else {
            v[i] = rand() % 10000;
        }
    }
}

/* CÓPIA DE VETORES */

/* Copia os elementos de origem para destino.

A cópia é feita posição por posição.
O vetor de origem permanece inalterado.

Exemplo:
origem = [4, 2, 8]
destino = [0, 0, 0]

Após a cópia:
destino = [4, 2, 8]
*/
void vetor_copiar(int *destino, const int *origem, int n) {

    // Verifica se os ponteiros são válidos e se existe pelo menos um elemento para copiar.
    if (destino == NULL || origem == NULL || n <= 0) return;

    // Percorre as posições e realiza a cópia.
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

/* IMPRESSÃO DO VETOR */

/* Exibe todos os elementos do vetor.

Os valores são apresentados entre colchetes,
separados por vírgulas.

Exemplo:
[ 10, 20, 30 ]
*/
void vetor_imprimir(const int *v, int n) {

    // Informa que não existe um vetor válido para exibir.
    if (v == NULL || n <= 0) {
        puts("(vetor vazio)");
        return;
    }

    printf("[");

    // Percorre o vetor e imprime cada elemento.
    for (int i = 0; i < n; i++) {

        // Evita colocar uma vírgula antes do primeiro elemento.
        printf("%s%d", i == 0 ? " " : ", ", v[i]);
    }

    // Fecha a representação do vetor.
    puts(" ]");
}

/* VERIFICAÇÃO DE ORDENAÇÃO */

/* Verifica se o vetor está em ordem crescente
ou se seus elementos estão repetidos.

A verificação compara cada elemento com o anterior.

Exemplos:
[1, 2, 3, 4] - ordenado.
[1, 2, 2, 4] - ordenado.
[1, 3, 2, 4] - não ordenado.

A função aceita valores repetidos porque
verifica a ordem não decrescente.
*/
int vetor_ordenado(const int *v, int n) { // Retorna 1 se o vetor estiver ordenado ou 0 se estiver vazio, inválido ou fora de ordem.

    // Vetor inválido ou vazio não é considerado ordenado.
    if (v == NULL || n <= 0) return 0;

    // Começa na segunda posição para comparar cada elemento com o anterior.
    for (int i = 1; i < n; i++) {

        // Verifica se existe uma quebra na ordem crescente.
        if (v[i - 1] > v[i]) {
            return 0;
        }
    }

    // Todos os elementos estão em ordem não decrescente.
    return 1;
}

/* IDENTIFICAÇÃO DO TIPO DE DADOS */

/* Converte o valor do enum em um texto.

Facilita a apresentação do tipo de conjunto
de dados nos relatórios do programa.
*/
const char *vetor_nome_tipo(TipoDados tipo) { // Retorna o nome correspondente ao tipo de dados ou "Desconhecido" para valores não previstos.

    switch (tipo) {

        case DADOS_ALEATORIOS:
            return "Aleatorio";

        case DADOS_ORDENADOS:
            return "Ordenado";

        case DADOS_INVERTIDOS:
            return "Invertido";

        // Trata valores que não correspondem às opções previstas.
        default:
            return "Desconhecido";
    }
}
