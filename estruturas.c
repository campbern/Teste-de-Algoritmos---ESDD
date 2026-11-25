#include <limits.h> // Verifica o limite de elementos da lista circular (INT_MAX).
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "estruturas.h"


/* LISTA SIMPLESMENTE ENCADEADA */

/* Inicializa uma lista vazia.
O ponteiro inicio recebe NULL porque ainda não existem nós.
*/
void lista_iniciar(Lista *l) {
    if (l == NULL) return;

    l->inicio = NULL;
}

 /* Insere um novo elemento no início da lista.
A inserção no início é O(1), pois não é necessário percorrer os elementos existentes.
*/
int lista_inserir(Lista *l, int valor) { // Retorna 1 em caso de sucesso ou 0 em caso de falha.
    if (l == NULL) return 0;

    // Reserva memória para o novo nó.
    NoLista *novo = malloc(sizeof(*novo));

    if (novo == NULL) return 0;

    novo->valor = valor;

    // O novo nó aponta para o antigo primeiro elemento.
    novo->prox = l->inicio;

    // O novo nó passa a ser o início da lista.
    l->inicio = novo;

    return 1;
}

/* Remove a primeira ocorrência de um valor.
O ponteiro para ponteiro permite alterar diretamente o endereço que aponta para o nó removido.
Dessa forma, o mesmo procedimento funciona tanto para remover o primeiro nó quanto os seguintes.
*/
int lista_remover(Lista *l, int valor) { // Retorna 1 se remover o valor ou 0 se não encontrar ou ocorrer falha.
    if (l == NULL) return 0;

    // Começa apontando para o endereço do início da lista.
    NoLista **atual = &l->inicio;

    while (*atual != NULL) {
        if ((*atual)->valor == valor) {
            NoLista *rem = *atual;

            // O nó anterior passa a apontar para o próximo.
            *atual = rem->prox;

            // Libera a memória do nó removido.
            free(rem);

            return 1;
        }

        // Avança para o endereço do próximo ponteiro.
        atual = &(*atual)->prox;
    }

    // O valor não foi encontrado.
    return 0;
}

/* Procura um valor na lista.
iteracoes contabiliza quantos nós foram examinados.
*/
int lista_buscar(const Lista *l, int valor, long long *iteracoes) { // Retorna 1 se encontrar o valor ou 0 caso contrário.
    if (iteracoes == NULL) return 0;

    *iteracoes = 0;

    if (l == NULL) return 0;

    const NoLista *p = l->inicio;

    while (p != NULL) {
        (*iteracoes)++;

        if (p->valor == valor) return 1;

        p = p->prox;
    }

    return 0;
}

/* Percorre a lista e exibe seus elementos.
O último elemento aponta para NULL, indicando o fim da lista.
*/
void lista_imprimir(const Lista *l) {
    if (l == NULL) {
        puts("Lista invalida.");
        return;
    }

    const NoLista *p = l->inicio;

    printf("Lista: ");

    while (p != NULL) {
        printf("%d -> ", p->valor);
        p = p->prox;
    }

    puts("NULL");
}

/* Libera todos os nós da lista.
O início é atualizado antes de liberar cada nó, evitando acessar uma posição de memória já liberada.
*/
void lista_liberar(Lista *l) {
    if (l == NULL) return;

    while (l->inicio != NULL) {
        NoLista *p = l->inicio;

        l->inicio = p->prox;

        free(p);
    }
}


/* PILHA */

/* Inicializa a pilha.
O topo começa em -1 para indicar que não há elementos.
A memória é reservada dinamicamente conforme a capacidade.
*/
int pilha_iniciar(Pilha *p, int capacidade) { // Retorna 1 se a inicialização for concluída ou 0 em caso de falha.
    if (p == NULL) return 0;

    // Define um estado seguro antes de tentar alocar memória.
    // Isso também permite chamar pilha_liberar() caso a inicialização falhe.
    p->dados = NULL;
    p->topo = -1;
    p->capacidade = 0;

    // A capacidade precisa ser positiva.
    if (capacidade <= 0) return 0;

    // Evita overflow no cálculo do tamanho da alocação.
    if ((size_t)capacidade > SIZE_MAX / sizeof(int)) {
        return 0;
    }

    // Reserva espaço para a quantidade solicitada de inteiros.
    p->dados = malloc((size_t)capacidade * sizeof(int));

    if (p->dados == NULL) return 0;

    p->capacidade = capacidade;

    return 1;
}

/* Insere um elemento no topo da pilha.
A operação push segue o princípio LIFO.
*/
int pilha_push(Pilha *p, int valor) { // Retorna 1 se inserir o elemento ou 0 se a operação não for possível.
    if (p == NULL || p->dados == NULL) return 0;

    // Impede a inserção quando a capacidade foi atingida.
    if (p->topo >= p->capacidade - 1) return 0;

    // Avança o topo e armazena o novo valor.
    p->topo++;

    p->dados[p->topo] = valor;

    return 1;
}

/* Remove o elemento que está no topo da pilha.
O valor removido é devolvido por meio do ponteiro valor.
*/
int pilha_pop(Pilha *p, int *valor) { // Retorna 1 se remover o elemento ou 0 se a pilha estiver vazia ou inválida.
    if (p == NULL || p->dados == NULL || valor == NULL) {
        return 0;
    }

    // Não é possível remover elementos de uma pilha vazia.
    if (p->topo < 0) return 0;

    // Recupera o elemento do topo.
    *valor = p->dados[p->topo];

    // Atualiza o topo para a posição anterior.
    p->topo--;

    return 1;
}

/* Exibe os elementos da pilha da base até o topo.
*/
void pilha_imprimir(const Pilha *p) {
    if (p == NULL || p->dados == NULL) {
        puts("Pilha nao inicializada.");
        return;
    }

    printf("Pilha (base -> topo): ");

    for (int i = 0; i <= p->topo; i++) {
        printf("%d ", p->dados[i]);
    }

    puts("");
}

/* Libera a memória da pilha e restaura seus campos para um estado vazio.
*/
void pilha_liberar(Pilha *p) {
    if (p == NULL) return;

    free(p->dados);

    p->dados = NULL;
    p->topo = -1;
    p->capacidade = 0;
}


/* FILA CIRCULAR */

/* Inicializa a fila circular.
inicio indica de onde será removido o próximo elemento.
fim indica onde será inserido o próximo elemento.
quantidade controla quantos elementos estão armazenados.
*/
int fila_iniciar(Fila *f, int capacidade) { // Retorna 1 se a inicialização for concluída ou 0 em caso de falha.
    if (f == NULL) return 0;

    // Define o estado inicial da fila.
    f->dados = NULL;
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
    f->capacidade = 0;

    if (capacidade <= 0) return 0;

    // Verifica se o tamanho da alocação é representável.
    if ((size_t)capacidade > SIZE_MAX / sizeof(int)) {
        return 0;
    }

    // Reserva memória para os elementos da fila.
    f->dados = malloc((size_t)capacidade * sizeof(int));

    if (f->dados == NULL) return 0;

    f->capacidade = capacidade;

    return 1;
}

/* Insere um elemento no final da fila.
O índice fim avança circularmente.
Quando chega ao final do vetor, retorna à posição zero.
*/
int fila_enfileirar(Fila *f, int valor) { // Retorna 1 se inserir o elemento ou 0 se a fila estiver cheia ou inválida.
    if (f == NULL || f->dados == NULL) return 0;

    // Impede a inserção quando a fila está cheia.
    if (f->quantidade >= f->capacidade) return 0;

    f->dados[f->fim] = valor;

    // Avança fim de forma circular.
    f->fim = (f->fim + 1) % f->capacidade;

    f->quantidade++;

    return 1;
}

/* Remove o primeiro elemento da fila.
O valor removido é devolvido por meio do ponteiro valor.
*/
int fila_desenfileirar(Fila *f, int *valor) { // Retorna 1 se remover o elemento ou 0 se a fila estiver vazia ou inválida.
    if (f == NULL || f->dados == NULL || valor == NULL) {
        return 0;
    }

    // Não é possível remover elementos de uma fila vazia.
    if (f->quantidade == 0) return 0;

    *valor = f->dados[f->inicio];

    // Avança inicio de forma circular.
    f->inicio = (f->inicio + 1) % f->capacidade;

    f->quantidade--;

    return 1;
}

/* Exibe os elementos da fila na ordem em que serão removidos.
O percurso começa em inicio e considera somente as posições ocupadas.
*/
void fila_imprimir(const Fila *f) {
    if (f == NULL || f->dados == NULL) {
        puts("Fila nao inicializada.");
        return;
    }

    printf("Fila (inicio -> fim): ");

    int pos = f->inicio;

    for (int i = 0; i < f->quantidade; i++) {
        printf("%d ", f->dados[pos]);

        // Avança circularmente sem somar inicio + i.
        pos++;

        if (pos == f->capacidade) {
            pos = 0;
        }
    }

    puts("");
}

/* Libera a memória da fila e restaura seus campos.
*/
void fila_liberar(Fila *f) {
    if (f == NULL) return;

    free(f->dados);

    f->dados = NULL;
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
    f->capacidade = 0;
}


/* ÁRVORE BINÁRIA DE BUSCA */

/* Insere um valor na árvore binária de busca.
A inserção é recursiva:
valores menores seguem para a esquerda;
valores maiores seguem para a direita.
Valores iguais não criam novos nós.
*/
int arvore_inserir(NoArvore **raiz, int valor) { // Retorna 1 se a operação for aceita ou 0 em caso de falha.
    if (raiz == NULL) return 0;

    // Encontrou uma posição vazia para inserir o novo nó.
    if (*raiz == NULL) {
        NoArvore *novo = malloc(sizeof(*novo));

        if (novo == NULL) return 0;

        novo->valor = valor;
        novo->esq = NULL;
        novo->dir = NULL;

        *raiz = novo;

        return 1;
    }

    if (valor < (*raiz)->valor) {
        // Continua a inserção na subárvore esquerda.
        return arvore_inserir(&(*raiz)->esq, valor);
    }

    if (valor > (*raiz)->valor) {
        // Continua a inserção na subárvore direita.
        return arvore_inserir(&(*raiz)->dir, valor);
    }

    // O valor já existe. A operação é aceita, mas nenhum nó novo é criado.
    return 1;
}

/* Procura um valor na árvore.
A comparação permite escolher apenas uma subárvore a cada etapa, desde que a árvore respeite sua organização.
*/
int arvore_buscar(const NoArvore *raiz, int valor,
                  long long *iteracoes) { // Retorna 1 se encontrar o valor ou 0 caso contrário.

    if (iteracoes == NULL) return 0;

    *iteracoes = 0;

    while (raiz != NULL) {
        // Conta o nó examinado.
        (*iteracoes)++;

        if (valor == raiz->valor) return 1;

        if (valor < raiz->valor) {
            raiz = raiz->esq;
        } else {
            raiz = raiz->dir;
        }
    }

    return 0;
}

/* Percurso em ordem (in-order).
A ordem de visita é: subárvore esquerda, nó atual e subárvore direita.
Em uma árvore binária de busca, esse percurso apresenta os valores em ordem crescente.
*/
void arvore_em_ordem(const NoArvore *raiz) {
    if (raiz == NULL) return;

    arvore_em_ordem(raiz->esq);

    printf("%d ", raiz->valor);

    arvore_em_ordem(raiz->dir);
}

/* Libera todos os nós da árvore.
A liberação ocorre em pós-ordem: subárvore esquerda, subárvore direita e nó atual.
Assim, os filhos são liberados antes do nó que os referencia.
*/
void arvore_liberar(NoArvore *raiz) {
    if (raiz == NULL) return;

    arvore_liberar(raiz->esq);

    arvore_liberar(raiz->dir);

    free(raiz);
}


/* TABELA HASH COM ENCADEAMENTO */

/* Calcula o índice correspondente a uma chave.
O cast para unsigned permite trabalhar com chaves negativas sem produzir um índice negativo.
O operador módulo garante um índice entre zero e HASH_CAPACIDADE - 1.
*/
static unsigned hash_indice(int chave) {
    unsigned x = (unsigned)chave;

    return x % HASH_CAPACIDADE;
}

/* Inicializa todas as posições da tabela como vazias.
Cada posição representa o início de uma lista encadeada.
*/
void hash_iniciar(NoHash *tabela[HASH_CAPACIDADE]) {
    if (tabela == NULL) return;

    for (int i = 0; i < HASH_CAPACIDADE; i++) {
        tabela[i] = NULL;
    }
}

/* Insere uma chave na tabela hash.
Primeiro calcula o índice da chave e percorre a lista daquela posição para verificar se a chave já existe.
Caso não exista, cria um novo nó no início da lista.
*/
int hash_inserir(NoHash *tabela[HASH_CAPACIDADE], int chave) { // Retorna 1 se a operação for aceita ou 0 em caso de falha.
    if (tabela == NULL) return 0;

    unsigned indice = hash_indice(chave);

    NoHash *p = tabela[indice];

    // Evita inserir a mesma chave mais de uma vez.
    while (p != NULL) {
        if (p->chave == chave) return 1;

        p = p->prox;
    }

    // Reserva memória para a nova chave.
    NoHash *novo = malloc(sizeof(*novo));

    if (novo == NULL) return 0;

    novo->chave = chave;

    // Insere o novo nó no início da lista da posição.
    novo->prox = tabela[indice];

    tabela[indice] = novo;

    return 1;
}

/* Procura uma chave na tabela hash.
Primeiro calcula a posição correspondente.
Depois percorre somente a lista daquela posição.
iteracoes contabiliza os nós examinados.
*/
int hash_buscar(NoHash *tabela[HASH_CAPACIDADE],
                int chave, long long *iteracoes) { // Retorna 1 se encontrar a chave ou 0 caso contrário.

    if (iteracoes == NULL) return 0;

    *iteracoes = 0;

    if (tabela == NULL) return 0;

    unsigned indice = hash_indice(chave);

    NoHash *p = tabela[indice];

    while (p != NULL) {
        (*iteracoes)++;

        if (p->chave == chave) return 1;

        p = p->prox;
    }

    return 0;
}

/* Exibe somente as posições ocupadas da tabela.
Cada posição pode conter uma lista de nós devido às colisões entre chaves.
*/
void hash_imprimir(NoHash *tabela[HASH_CAPACIDADE]) {
    if (tabela == NULL) return;

    int vazia = 1;

    for (int i = 0; i < HASH_CAPACIDADE; i++) {
        if (tabela[i] != NULL) {
            vazia = 0;

            printf("[%d]: ", i);

            NoHash *p = tabela[i];

            while (p != NULL) {
                printf("%d -> ", p->chave);

                p = p->prox;
            }

            puts("NULL");
        }
    }

    if (vazia) {
        puts("Tabela hash vazia.");
    }
}

/* Libera todos os nós de todas as listas da tabela.
Cada posição é percorrida até que sua lista esteja vazia.
*/
void hash_liberar(NoHash *tabela[HASH_CAPACIDADE]) {
    if (tabela == NULL) return;

    for (int i = 0; i < HASH_CAPACIDADE; i++) {
        while (tabela[i] != NULL) {
            NoHash *p = tabela[i];

            tabela[i] = p->prox;

            free(p);
        }
    }
}


/* LISTA ESTÁTICA */

/* Inicializa uma lista estática.
A lista utiliza um vetor alocado dinamicamente.
A capacidade define o limite máximo de elementos.
A quantidade começa em zero, indicando lista vazia.
*/
int lista_estatica_iniciar(ListaEstatica *l, int capacidade) { // Retorna 1 se a inicialização for concluída ou 0 em caso de falha.
    if (l == NULL) return 0;

    // Define o estado inicial da lista.
    l->dados = NULL;
    l->quantidade = 0;
    l->capacidade = 0;

    // A capacidade precisa ser positiva.
    if (capacidade <= 0) return 0;

    // Evita overflow no cálculo do tamanho da alocação.
    if ((size_t)capacidade > SIZE_MAX / sizeof(int)) {
        return 0;
    }

    // Reserva memória para armazenar os elementos.
    l->dados = malloc((size_t)capacidade * sizeof(int));

    if (l->dados == NULL) return 0;

    l->capacidade = capacidade;

    return 1;
}

/* Insere um elemento no final da lista.
Como os elementos são armazenados em posições consecutivas, a inserção ocorre na posição indicada pela quantidade atual de elementos.
A operação é O(1), pois não exige deslocamentos.
*/
int lista_estatica_inserir(ListaEstatica *l, int valor) { // Retorna 1 se inserir o elemento ou 0 se a operação não for possível.
    if (l == NULL || l->dados == NULL) return 0;

    // Impede a inserção quando a capacidade foi atingida.
    if (l->quantidade >= l->capacidade) return 0;

    // Armazena o valor na próxima posição disponível.
    l->dados[l->quantidade] = valor;

    // Atualiza a quantidade de elementos.
    l->quantidade++;

    return 1;
}

/* Remove a primeira ocorrência de um valor.
Após encontrar o elemento, os valores posteriores são deslocados uma posição para a esquerda.
Dessa forma, não ficam espaços vazios entre os elementos.
*/
int lista_estatica_remover(ListaEstatica *l, int valor) { // Retorna 1 se remover o valor ou 0 se não encontrar ou ocorrer falha.
    if (l == NULL || l->dados == NULL) return 0;

    // Procura a posição do valor informado.
    int indice = 0;

    while (indice < l->quantidade &&
           l->dados[indice] != valor) {
        indice++;
    }

    // O valor não foi encontrado.
    if (indice == l->quantidade) return 0;

    // Desloca os elementos seguintes para a esquerda, sobrescrevendo a posição do elemento removido.
    for (int i = indice; i < l->quantidade - 1; i++) {
        l->dados[i] = l->dados[i + 1];
    }

    // Atualiza a quantidade de elementos armazenados.
    l->quantidade--;

    return 1;
}

/* Procura um valor na lista estática.
A busca é sequencial, pois os elementos não precisam estar ordenados.
iteracoes contabiliza quantas posições foram examinadas.
*/
int lista_estatica_buscar(const ListaEstatica *l, int valor,
                          long long *iteracoes) { // Retorna 1 se encontrar o valor ou 0 caso contrário.
    if (iteracoes == NULL) return 0;

    *iteracoes = 0;

    if (l == NULL || l->dados == NULL) return 0;

    for (int i = 0; i < l->quantidade; i++) {
        // Conta a posição examinada.
        (*iteracoes)++;

        if (l->dados[i] == valor) return 1;
    }

    return 0;
}

/* Exibe os elementos armazenados na lista estática.
Somente as posições ocupadas são exibidas.
*/
void lista_estatica_imprimir(const ListaEstatica *l) {
    if (l == NULL || l->dados == NULL) {
        puts("Lista estatica nao inicializada.");
        return;
    }

    printf("Lista estatica: ");

    for (int i = 0; i < l->quantidade; i++) {
        printf("%d ", l->dados[i]);
    }

    puts("");
}

/* Libera a memória utilizada pela lista estática.
Os campos são restaurados para representar uma lista vazia e não inicializada.
*/
void lista_estatica_liberar(ListaEstatica *l) {
    if (l == NULL) return;

    free(l->dados);

    l->dados = NULL;
    l->quantidade = 0;
    l->capacidade = 0;
}


/* LISTA DUPLAMENTE ENCADEADA */

/* Inicializa uma lista duplamente encadeada vazia.
Os ponteiros inicio e fim recebem NULL porque ainda não existem elementos armazenados.
*/
void lista_dupla_iniciar(ListaDupla *l) {
    if (l == NULL) return;

    l->inicio = NULL;
    l->fim = NULL;
}

/* Insere um novo elemento no início da lista.
O novo nó aponta para o antigo primeiro elemento.
O ponteiro ant do antigo primeiro nó passa a apontar para o novo elemento.
Se a lista estiver vazia, o novo nó será simultaneamente o início e o fim.
*/
int lista_dupla_inserir(ListaDupla *l, int valor) { // Retorna 1 se inserir o elemento ou 0 em caso de falha.
    if (l == NULL) return 0;

    // Reserva memória para o novo nó.
    NoListaDupla *novo = malloc(sizeof(*novo));

    if (novo == NULL) return 0;

    novo->valor = valor;

    // O novo nó será o primeiro, portanto não possui anterior.
    novo->ant = NULL;

    // O próximo será o antigo primeiro elemento.
    novo->prox = l->inicio;

    if (l->inicio != NULL) {
        // O antigo primeiro nó passa a apontar para o novo.
        l->inicio->ant = novo;
    } else {
        // Se a lista estava vazia, o novo elemento também será o último.
        l->fim = novo;
    }

    // Atualiza o início da lista.
    l->inicio = novo;

    return 1;
}

/* Remove a primeira ocorrência de um valor.
Como a lista possui ponteiros para o elemento anterior e para o próximo, é possível atualizar as ligações diretamente, sem percorrer novamente a estrutura.
O procedimento também trata a remoção do primeiro e do último elemento.
*/
int lista_dupla_remover(ListaDupla *l, int valor) { // Retorna 1 se remover o valor ou 0 se não encontrar ou ocorrer falha.
    if (l == NULL) return 0;

    // Percorre a lista procurando o valor.
    NoListaDupla *p = l->inicio;

    while (p != NULL && p->valor != valor) {
        p = p->prox;
    }

    // O valor não foi encontrado.
    if (p == NULL) return 0;

    if (p->ant != NULL) {
        // O elemento anterior passa a apontar para o próximo.
        p->ant->prox = p->prox;
    } else {
        // O elemento removido era o primeiro.
        l->inicio = p->prox;
    }

    if (p->prox != NULL) {
        // O próximo elemento passa a apontar para o anterior.
        p->prox->ant = p->ant;
    } else {
        // O elemento removido era o último.
        l->fim = p->ant;
    }

    // Libera a memória do nó removido.
    free(p);

    return 1;
}

/* Procura um valor na lista duplamente encadeada.
O percurso começa no primeiro elemento e avança utilizando o ponteiro prox.
iteracoes contabiliza os nós examinados.
*/
int lista_dupla_buscar(const ListaDupla *l, int valor,
                       long long *iteracoes) { // Retorna 1 se encontrar o valor ou 0 caso contrário.
    if (iteracoes == NULL) return 0;

    *iteracoes = 0;

    if (l == NULL) return 0;

    const NoListaDupla *p = l->inicio;

    while (p != NULL) {
        (*iteracoes)++;

        if (p->valor == valor) return 1;

        p = p->prox;
    }

    return 0;
}

/* Exibe os elementos do início ao fim.
O percurso utiliza o ponteiro prox de cada nó.
*/
void lista_dupla_imprimir(const ListaDupla *l) {
    if (l == NULL) {
        puts("Lista duplamente encadeada invalida.");
        return;
    }

    const NoListaDupla *p = l->inicio;

    printf("Lista dupla (inicio -> fim): ");

    while (p != NULL) {
        printf("%d <-> ", p->valor);

        p = p->prox;
    }

    puts("NULL");
}

/* Exibe os elementos do fim ao início.
O percurso utiliza o ponteiro ant de cada nó, demonstrando a navegação no sentido inverso.
*/
void lista_dupla_imprimir_reversa(const ListaDupla *l) {
    if (l == NULL) {
        puts("Lista duplamente encadeada invalida.");
        return;
    }

    const NoListaDupla *p = l->fim;

    printf("Lista dupla (fim -> inicio): ");

    while (p != NULL) {
        printf("%d <-> ", p->valor);

        p = p->ant;
    }

    puts("NULL");
}

/* Libera todos os nós da lista duplamente encadeada.
O percurso começa no início e avança pelo ponteiro prox.
Antes de liberar cada nó, o endereço do próximo é salvo.
Ao final, inicio e fim são definidos como NULL.
*/
void lista_dupla_liberar(ListaDupla *l) {
    if (l == NULL) return;

    while (l->inicio != NULL) {
        NoListaDupla *p = l->inicio;

        // Salva o próximo elemento antes de liberar o atual.
        l->inicio = p->prox;

        free(p);
    }

    // A lista fica completamente vazia.
    l->fim = NULL;
}


/* LISTA CIRCULAR SIMPLESMENTE ENCADEADA */

/* Inicializa uma lista circular vazia.
Os ponteiros inicio e fim recebem NULL.
A quantidade começa em zero.
Quando a lista possuir elementos, o último nó deverá apontar novamente para o primeiro.
*/
void lista_circular_iniciar(ListaCircular *l) {
    if (l == NULL) return;

    l->inicio = NULL;
    l->fim = NULL;
    l->quantidade = 0;
}

/* Insere um novo elemento no final da lista circular.
Se a lista estiver vazia, o novo nó aponta para si mesmo.
Caso já existam elementos, o novo nó aponta para o início, o antigo último nó aponta para o novo e o ponteiro fim é atualizado.
Dessa forma, a ligação circular é preservada.
*/
int lista_circular_inserir(ListaCircular *l, int valor) { // Retorna 1 se inserir o elemento ou 0 em caso de falha.
    if (l == NULL) return 0;

    // Evita ultrapassar o limite do campo quantidade.
    if (l->quantidade == INT_MAX) return 0;

    // Reserva memória para o novo nó.
    NoListaCircular *novo = malloc(sizeof(*novo));

    if (novo == NULL) return 0;

    novo->valor = valor;

    if (l->inicio == NULL) {
        // Primeiro elemento: início e fim apontam para o mesmo nó.
        // Como existe apenas um elemento, ele aponta para si mesmo.
        l->inicio = novo;
        l->fim = novo;

        novo->prox = novo;
    } else {
        // Insere depois do último elemento e mantém a ligação com o início.
        novo->prox = l->inicio;

        // O antigo último nó passa a apontar para o novo.
        l->fim->prox = novo;

        // Atualiza o último elemento.
        l->fim = novo;
    }

    // Atualiza a quantidade de elementos.
    l->quantidade++;

    return 1;
}

/* Remove a primeira ocorrência de um valor.
Como a lista é circular, não existe um ponteiro NULL indicando o final do percurso.
Por isso, a quantidade de elementos controla quantos nós devem ser examinados.
São tratados três casos: remoção do único elemento, do primeiro ou último elemento e de um elemento intermediário.
*/
int lista_circular_remover(ListaCircular *l, int valor) { // Retorna 1 se remover o valor ou 0 se não encontrar ou ocorrer falha.
    if (l == NULL || l->inicio == NULL) return 0;

    // Começa no primeiro elemento.
    NoListaCircular *atual = l->inicio;

    // Inicialmente, o anterior é o último elemento.
    NoListaCircular *anterior = l->fim;

    // Percorre somente a quantidade de nós existentes para evitar um loop infinito.
    for (int i = 0; i < l->quantidade; i++) {
        if (atual->valor == valor) {

            if (l->quantidade == 1) {
                // A remoção do único elemento deixa a lista vazia.
                l->inicio = NULL;
                l->fim = NULL;
            } else {
                // O anterior passa a apontar para o próximo, retirando o nó atual da sequência.
                anterior->prox = atual->prox;

                if (atual == l->inicio) {
                    // Atualiza o início se o primeiro foi removido.
                    l->inicio = atual->prox;
                }

                if (atual == l->fim) {
                    // Atualiza o fim se o último foi removido.
                    l->fim = anterior;
                }

                // Garante que o último elemento continue apontando para o primeiro.
                l->fim->prox = l->inicio;
            }

            // Libera a memória do nó removido.
            free(atual);

            // Atualiza a quantidade de elementos.
            l->quantidade--;

            return 1;
        }

        // Avança os ponteiros para o próximo nó.
        anterior = atual;
        atual = atual->prox;
    }

    // O valor não foi encontrado.
    return 0;
}

/* Procura um valor na lista circular.
O percurso começa no início e utiliza o ponteiro prox.
Como o último nó aponta para o primeiro, a quantidade controla o limite da busca.
iteracoes contabiliza os nós examinados.
*/
int lista_circular_buscar(const ListaCircular *l, int valor,
                          long long *iteracoes) { // Retorna 1 se encontrar o valor ou 0 caso contrário.
    if (iteracoes == NULL) return 0;

    *iteracoes = 0;

    if (l == NULL || l->inicio == NULL) return 0;

    const NoListaCircular *p = l->inicio;

    for (int i = 0; i < l->quantidade; i++) {
        (*iteracoes)++;

        if (p->valor == valor) return 1;

        p = p->prox;
    }

    return 0;
}

/* Exibe os elementos da lista circular.
O percurso começa no primeiro nó e visita exatamente a quantidade de elementos armazenados.
Ao terminar, o ponteiro retorna ao início da lista.
*/
void lista_circular_imprimir(const ListaCircular *l) {
    if (l == NULL) {
        puts("Lista circular invalida.");
        return;
    }

    if (l->inicio == NULL) {
        puts("Lista circular vazia.");
        return;
    }

    const NoListaCircular *p = l->inicio;

    printf("Lista circular: ");

    for (int i = 0; i < l->quantidade; i++) {
        printf("%d -> ", p->valor);

        p = p->prox;
    }

    printf("(retorna ao inicio)\n");
}

/* Libera todos os nós da lista circular.
Como os nós formam um ciclo, não é possível utilizar simplesmente a condição p != NULL para encerrar o percurso.
A quantidade de elementos determina quantos nós precisam ser liberados.
*/
void lista_circular_liberar(ListaCircular *l) {
    if (l == NULL) return;

    NoListaCircular *p = l->inicio;

    for (int i = 0; i < l->quantidade; i++) {
        // Salva o endereço do próximo nó antes de liberar o atual.
        NoListaCircular *proximo = p->prox;

        free(p);

        p = proximo;
    }

    // Restaura o estado de lista vazia.
    l->inicio = NULL;
    l->fim = NULL;
    l->quantidade = 0;
}
