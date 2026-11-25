#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "ordenacao.h"
#include "vetor.h"

/* Variável estática que controla a exibição dos passos.

Por ser static, seu acesso fica restrito a este arquivo.
*/
static int passo_ativo = 0;

/* Configura a exibição dos passos da ordenação.

Quando ativo for diferente de zero, o vetor será
exibido durante a execução dos algoritmos.
*/
void ordenacao_passo_configurar(int ativo) {
    passo_ativo = ativo;
}

/* Exibe o estado atual do vetor e aguarda o usuário
pressionar Enter para continuar.

A função só é executada quando a visualização
dos passos está ativada.
*/
static void mostrar_passo(const int *v, int n) {
    if (!passo_ativo) return;

    vetor_imprimir(v, n);

    printf("Enter para continuar...");
    fflush(stdout);

    // Consome os caracteres até encontrar uma quebra de linha ou o fim da entrada.
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/* Realiza a troca de posição entre dois elementos.

Se os índices forem iguais, não existe troca efetiva.

Métricas:
Uma troca e três movimentações: duas leituras e uma
utilização da variável auxiliar para efetivar a permuta.
*/
static void trocar(int *v, int i, int j, int n, Metricas *m) {
    if (i == j) return;

    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;

    m->trocas++;
    m->movimentacoes += 3;

    mostrar_passo(v, n);
}

/* BUBBLE SORT */

/* Percorre o vetor comparando elementos vizinhos.

Quando dois elementos estão fora de ordem, eles são
trocados de posição.

A cada passagem, o maior elemento ainda não ordenado
é deslocado para o final do trecho analisado.

A variável mudou permite encerrar antecipadamente
quando nenhuma troca acontece em uma passagem.
*/
int bubble_sort(int *v, int n, Metricas *m) { // Retorna 1 se a execução for válida ou 0 se os parâmetros forem inválidos.
    if (v == NULL || m == NULL || n < 0) return 0;

    strcpy(m->nome, "Bubble");

    for (int i = 0; i < n - 1; i++) {
        int mudou = 0;

        for (int j = 0; j < n - 1 - i; j++) {
            // Registra a comparação entre elementos vizinhos.
            m->comparacoes++;

            if (v[j] > v[j + 1]) {
                trocar(v, j, j + 1, n, m);
                mudou = 1;
            }
        }

        // Se não houve troca, o vetor já está ordenado.
        if (!mudou) break;
    }

    return 1;
}

/* SELECTION SORT */

/* Percorre o trecho ainda não ordenado procurando
o menor elemento.

Ao final de cada passagem, coloca esse elemento
na posição correta.

Diferentemente do Bubble Sort, realiza no máximo
uma troca efetiva por passagem.
*/
int selection_sort(int *v, int n, Metricas *m) { // Retorna 1 se a execução for válida ou 0 se os parâmetros forem inválidos.
    if (v == NULL || m == NULL || n < 0) return 0;

    strcpy(m->nome, "Selection");

    for (int i = 0; i < n - 1; i++) {
        // Inicialmente, considera o primeiro elemento do trecho como o menor.
        int menor = i;

        for (int j = i + 1; j < n; j++) {
            m->comparacoes++;

            // Atualiza a posição do menor elemento encontrado.
            if (v[j] < v[menor]) {
                menor = j;
            }
        }

        // Coloca o menor elemento na posição atual.
        // Se os índices forem iguais, não há troca efetiva.
        trocar(v, i, menor, n, m);
    }

    return 1;
}

/* INSERTION SORT */

/* Ordena o vetor construindo gradualmente um trecho ordenado.

Cada elemento é armazenado temporariamente na variável
chave e inserido na posição correta do trecho anterior.

Os elementos maiores que a chave são deslocados
uma posição para a direita.

Neste algoritmo, os deslocamentos e a gravação da chave
são contabilizados como movimentações, não como trocas.
*/
int insertion_sort(int *v, int n, Metricas *m) { // Retorna 1 se a execução for válida ou 0 se os parâmetros forem inválidos.
    if (v == NULL || m == NULL || n < 0) return 0;

    strcpy(m->nome, "Insertion");

    // O primeiro elemento é considerado inicialmente ordenado.
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;

        // Percorre o trecho ordenado de trás para frente,
        // deslocando os elementos maiores que a chave.
        while (j >= 0) {
            m->comparacoes++;

            if (v[j] > chave) {
                v[j + 1] = v[j];
                m->movimentacoes++;

                mostrar_passo(v, n);
                j--;
            } else {
                break;
            }
        }

        // Insere a chave na posição encontrada.
        v[j + 1] = chave;
        m->movimentacoes++;

        mostrar_passo(v, n);
    }

    return 1;
}

/* MERGE SORT */

/* Combina dois trechos previamente ordenados.

O primeiro trecho vai de ini até meio.
O segundo trecho vai de meio + 1 até fim.

Os elementos são comparados e copiados para o vetor
auxiliar na ordem correta.

Depois, o trecho ordenado é copiado de volta para v.
*/
static void merge(int *v, int *aux, int ini, int meio,
                  int fim, int n, Metricas *m) {

    int i = ini;
    int j = meio + 1;
    int k = ini;

    // Compara os elementos dos dois trechos.
    while (i <= meio && j <= fim) {
        m->comparacoes++;

        if (v[i] <= v[j]) {
            aux[k++] = v[i++];
        } else {
            aux[k++] = v[j++];
        }

        // Conta a cópia realizada para o vetor auxiliar.
        m->movimentacoes++;
    }

    // Copia os elementos restantes do primeiro trecho.
    while (i <= meio) {
        aux[k++] = v[i++];
        m->movimentacoes++;
    }

    // Copia os elementos restantes do segundo trecho.
    while (j <= fim) {
        aux[k++] = v[j++];
        m->movimentacoes++;
    }

    // Devolve os elementos ordenados ao vetor original.
    for (int p = ini; p <= fim; p++) {
        v[p] = aux[p];
        m->movimentacoes++;
    }

    mostrar_passo(v, n);
}

/* Divide recursivamente o vetor em trechos menores.

Quando os trechos possuem apenas um elemento,
a recursão retorna.

Em seguida, os trechos são combinados pelo merge().
*/
static void merge_rec(int *v, int *aux, int ini, int fim,
                      int n, Metricas *m) {

    // Condição de parada da recursão.
    if (ini >= fim) return;

    // Calcula o ponto médio evitando somar ini + fim.
    int meio = ini + (fim - ini) / 2;

    // Ordena recursivamente a primeira metade.
    merge_rec(v, aux, ini, meio, n, m);

    // Ordena recursivamente a segunda metade.
    merge_rec(v, aux, meio + 1, fim, n, m);

    // Combina as duas metades ordenadas.
    merge(v, aux, ini, meio, fim, n, m);
}

/* Função pública do Merge Sort.

Aloca um vetor auxiliar para armazenar temporariamente
os elementos durante a combinação dos trechos.

A execução é interrompida caso a alocação de memória falhe.
*/
int merge_sort(int *v, int n, Metricas *m) { // Retorna 1 se a execução for concluída ou 0 se os parâmetros forem inválidos ou a alocação falhar.
    if (v == NULL || m == NULL || n < 0) return 0;

    strcpy(m->nome, "Merge");

    // Vetores com zero ou um elemento já estão ordenados.
    if (n <= 1) return 1;

    // Verifica se o tamanho da alocação pode ser representado.
    if ((size_t)n > SIZE_MAX / sizeof(int)) {
        return 0;
    }

    // Reserva memória para o vetor auxiliar.
    int *aux = malloc((size_t)n * sizeof(int));

    if (aux == NULL) {
        fprintf(stderr, "Falha de memoria no Merge Sort.\n");
        return 0;
    }

    // Executa a divisão e combinação dos trechos.
    merge_rec(v, aux, 0, n - 1, n, m);

    // Libera a memória utilizada pelo vetor auxiliar.
    free(aux);

    return 1;
}

/* QUICK SORT */

/* Implementação recursiva do Quick Sort.

Utiliza o elemento central do trecho como pivô.

Dois índices percorrem o vetor:
i avança da esquerda para a direita.
j avança da direita para a esquerda.

Quando encontram elementos que precisam mudar
de posição, eles são trocados.

Depois da partição, o processo é repetido
recursivamente nos dois trechos resultantes.
*/
static void quick_rec(int *v, int ini, int fim, int n, Metricas *m) {
    // Encerra quando o trecho possui zero ou um elemento.
    if (ini >= fim) return;

    // Escolhe o elemento central como pivô.
    int pivo = v[ini + (fim - ini) / 2];

    int i = ini;
    int j = fim;

    while (i <= j) {

        // Avança enquanto os elementos forem menores que o pivô.
        while (i <= fim) {
            m->comparacoes++;

            if (v[i] < pivo) {
                i++;
            } else {
                break;
            }
        }

        // Retrocede enquanto os elementos forem maiores que o pivô.
        while (j >= ini) {
            m->comparacoes++;

            if (v[j] > pivo) {
                j--;
            } else {
                break;
            }
        }

        // Se os índices ainda não se cruzaram, realiza a troca.
        if (i <= j) {
            trocar(v, i, j, n, m);

            i++;
            j--;
        }
    }

    // Ordena recursivamente o trecho esquerdo.
    if (ini < j) {
        quick_rec(v, ini, j, n, m);
    }

    // Ordena recursivamente o trecho direito.
    if (i < fim) {
        quick_rec(v, i, fim, n, m);
    }
}

/* Função pública do Quick Sort.

Inicia o processo recursivo quando o vetor
possui pelo menos dois elementos.
*/
int quick_sort(int *v, int n, Metricas *m) { // Retorna 1 se a execução for válida ou 0 se os parâmetros forem inválidos.
    if (v == NULL || m == NULL || n < 0) return 0;

    strcpy(m->nome, "Quick");

    if (n > 1) {
        quick_rec(v, 0, n - 1, n, m);
    }

    return 1;
}
