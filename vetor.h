#ifndef VETOR_H
#define VETOR_H

/* Define os três tipos de conjuntos de dados
que podem ser gerados pelo programa.

Os valores numéricos permitem identificar
cada opção de forma simples.
*/
typedef enum {
    DADOS_ALEATORIOS = 1,
    DADOS_ORDENADOS = 2,
    DADOS_INVERTIDOS = 3
} TipoDados;

/* PROTÓTIPOS DAS FUNÇÕES DO MÓDULO */

/* Cria um vetor dinamicamente.

Parâmetro:
n - quantidade de elementos do vetor.
*/
int *vetor_criar(int n); // Retorna o ponteiro para o primeiro elemento do vetor ou NULL caso a criação falhe.

/* Preenche o vetor conforme o tipo de dados escolhido.

Parâmetros:
v - vetor que receberá os valores.
n - quantidade de elementos.
tipo - define se os dados serão aleatórios, ordenados ou invertidos.
*/
void vetor_gerar(int *v, int n, TipoDados tipo);

/* Copia os elementos de um vetor para outro.

Parâmetros:
destino - vetor que receberá a cópia.
origem - vetor que fornece os valores.
n - quantidade de elementos copiados.

O const impede que a função altere o vetor de origem.
*/
void vetor_copiar(int *destino, const int *origem, int n);

/* Exibe os elementos do vetor na tela.

Parâmetros:
v - vetor que será exibido.
n - quantidade de elementos.

A função não modifica os dados.
*/
void vetor_imprimir(const int *v, int n);

/* Verifica se os elementos estão em ordem crescente.

Parâmetros:
v - vetor que será verificado.
n - quantidade de elementos.
*/
int vetor_ordenado(const int *v, int n); // Retorna 1 se o vetor estiver em ordem não decrescente ou 0 se for inválido, vazio ou estiver fora de ordem.

/* Retorna o nome correspondente ao tipo de dados.

Parâmetro:
tipo - classificação do conjunto de dados.
*/
const char *vetor_nome_tipo(TipoDados tipo); // Retorna o texto correspondente ao tipo informado ou "Desconhecido" para valores não previstos.

#endif
