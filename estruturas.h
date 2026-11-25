#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H


/* LISTA SIMPLESMENTE ENCADEADA */

/* Cada nó armazena um valor inteiro e um ponteiro para o próximo nó.
A estrutura Lista mantém o endereço do primeiro elemento.
*/
typedef struct NoLista {
    int valor;              // Valor armazenado no nó.
    struct NoLista *prox;   // Endereço do próximo nó.
} NoLista;

typedef struct {
    NoLista *inicio;        // Primeiro elemento da lista.
} Lista;

/* Inicializa a lista como vazia.
*/
void lista_iniciar(Lista *l);

/* Insere um novo valor no início da lista.
*/
int lista_inserir(Lista *l, int valor); // Retorna 1 em caso de sucesso ou 0 em caso de falha.

/* Remove a primeira ocorrência do valor informado.
*/
int lista_remover(Lista *l, int valor); // Retorna 1 se remover ou 0 se não encontrar ou ocorrer falha.

/* Procura um valor e contabiliza os nós examinados.
*/
int lista_buscar(const Lista *l, int valor, long long *iteracoes); // Retorna 1 se encontrar ou 0 caso contrário.

/* Exibe os elementos da lista.
*/
void lista_imprimir(const Lista *l);

/* Libera todos os nós da lista.
*/
void lista_liberar(Lista *l);


/* LISTA ESTÁTICA */

/* Estrutura que utiliza um vetor alocado dinamicamente para armazenar uma quantidade limitada de elementos.
Os elementos ficam armazenados em posições consecutivas da memória.
A quantidade indica quantos elementos estão ocupados, enquanto capacidade representa o limite de armazenamento.
*/
typedef struct {
    int *dados;             // Vetor que armazena os elementos.
    int quantidade;         // Número atual de elementos.
    int capacidade;         // Quantidade máxima de elementos.
} ListaEstatica;

/* Inicializa a lista e reserva memória para sua capacidade.
*/
int lista_estatica_iniciar(ListaEstatica *l, int capacidade); // Retorna 1 em caso de sucesso ou 0 em caso de falha.

/* Insere um novo valor no final da lista.
*/
int lista_estatica_inserir(ListaEstatica *l, int valor); // Retorna 1 em caso de sucesso ou 0 se estiver cheia ou inválida.

/* Remove a primeira ocorrência do valor informado.
Os elementos posteriores são deslocados para preencher a posição que ficou vazia.
*/
int lista_estatica_remover(ListaEstatica *l, int valor); // Retorna 1 se remover ou 0 se não encontrar ou ocorrer falha.

/* Procura um valor e contabiliza as posições examinadas.
*/
int lista_estatica_buscar(const ListaEstatica *l, int valor,
                          long long *iteracoes); // Retorna 1 se encontrar ou 0 caso contrário.

/* Exibe os elementos armazenados na lista.
*/
void lista_estatica_imprimir(const ListaEstatica *l);

/* Libera o vetor utilizado pela lista.
*/
void lista_estatica_liberar(ListaEstatica *l);


/* LISTA DUPLAMENTE ENCADEADA */

/* Cada nó armazena um valor inteiro e dois ponteiros:
ant: endereço do nó anterior.
prox: endereço do próximo nó.
A estrutura ListaDupla mantém os endereços do primeiro e do último elemento.
Essa organização permite percorrer a lista nos dois sentidos.
*/
typedef struct NoListaDupla {
    int valor;                  // Valor armazenado no nó.
    struct NoListaDupla *ant;   // Endereço do nó anterior.
    struct NoListaDupla *prox;  // Endereço do próximo nó.
} NoListaDupla;

typedef struct {
    NoListaDupla *inicio;       // Primeiro elemento da lista.
    NoListaDupla *fim;          // Último elemento da lista.
} ListaDupla;

/* Inicializa a lista duplamente encadeada como vazia.
*/
void lista_dupla_iniciar(ListaDupla *l);

/* Insere um novo valor no início da lista.
Atualiza os ponteiros dos nós envolvidos.
*/
int lista_dupla_inserir(ListaDupla *l, int valor); // Retorna 1 em caso de sucesso ou 0 em caso de falha.

/* Remove a primeira ocorrência do valor informado.
Atualiza os ponteiros anterior e próximo dos nós vizinhos.
*/
int lista_dupla_remover(ListaDupla *l, int valor); // Retorna 1 se remover ou 0 se não encontrar ou ocorrer falha.

/* Procura um valor e contabiliza os nós examinados.
A busca percorre a lista do início ao fim.
*/
int lista_dupla_buscar(const ListaDupla *l, int valor,
                       long long *iteracoes); // Retorna 1 se encontrar ou 0 caso contrário.

/* Exibe os elementos do início ao fim.
*/
void lista_dupla_imprimir(const ListaDupla *l);

/* Exibe os elementos do fim ao início.
Demonstra a navegação pelo ponteiro anterior.
*/
void lista_dupla_imprimir_reversa(const ListaDupla *l);

/* Libera todos os nós da lista.
*/
void lista_dupla_liberar(ListaDupla *l);


/* LISTA CIRCULAR SIMPLESMENTE ENCADEADA */

/* Cada nó armazena um valor inteiro e um ponteiro para o próximo nó.
Diferentemente da lista simplesmente encadeada comum, o último nó não aponta para NULL.
O último elemento aponta novamente para o primeiro, formando uma estrutura circular.
A quantidade de elementos controla o percurso da lista.
*/
typedef struct NoListaCircular {
    int valor;                      // Valor armazenado no nó.
    struct NoListaCircular *prox;   // Próximo nó da lista.
} NoListaCircular;

typedef struct {
    NoListaCircular *inicio;        // Primeiro elemento.
    NoListaCircular *fim;           // Último elemento.
    int quantidade;                 // Número de elementos.
} ListaCircular;

/* Inicializa a lista circular como vazia.
*/
void lista_circular_iniciar(ListaCircular *l);

/* Insere um novo valor no final da lista.
O último nó continua apontando para o primeiro.
*/
int lista_circular_inserir(ListaCircular *l, int valor); // Retorna 1 em caso de sucesso ou 0 em caso de falha.

/* Remove a primeira ocorrência do valor informado.
Atualiza as ligações circulares entre os nós.
*/
int lista_circular_remover(ListaCircular *l, int valor); // Retorna 1 se remover ou 0 se não encontrar ou ocorrer falha.

/* Procura um valor e contabiliza os nós examinados.
O percurso respeita a quantidade de elementos.
*/
int lista_circular_buscar(const ListaCircular *l, int valor,
                          long long *iteracoes); // Retorna 1 se encontrar ou 0 caso contrário.

/* Exibe os elementos da lista circular.
O percurso termina após visitar todos os elementos.
*/
void lista_circular_imprimir(const ListaCircular *l);

/* Libera todos os nós da lista circular.
*/
void lista_circular_liberar(ListaCircular *l);


/* PILHA */

/* Estrutura baseada no princípio LIFO (Last In, First Out).
O último elemento inserido é o primeiro a ser removido.
O campo topo indica a posição do elemento mais recente.
Quando topo == -1, a pilha está vazia.
*/
typedef struct {
    int *dados;         // Vetor que armazena os elementos.
    int topo;           // Índice do elemento no topo.
    int capacidade;     // Quantidade máxima de elementos.
} Pilha;

/* Inicializa a pilha e reserva memória para sua capacidade.
*/
int pilha_iniciar(Pilha *p, int capacidade); // Retorna 1 em caso de sucesso ou 0 em caso de falha.

/* Insere um elemento no topo da pilha.
*/
int pilha_push(Pilha *p, int valor); // Retorna 1 em caso de sucesso ou 0 se estiver cheia ou inválida.

/* Remove o elemento do topo e o devolve por meio de valor.
*/
int pilha_pop(Pilha *p, int *valor); // Retorna 1 em caso de sucesso ou 0 se estiver vazia ou inválida.

/* Exibe os elementos da pilha.
*/
void pilha_imprimir(const Pilha *p);

/* Libera a memória utilizada pela pilha.
*/
void pilha_liberar(Pilha *p);


/* FILA CIRCULAR */

/* Estrutura baseada no princípio FIFO (First In, First Out).
O primeiro elemento inserido é o primeiro a ser removido.
Os índices inicio e fim avançam circularmente pelo vetor.
quantidade informa quantos elementos estão armazenados.
*/
typedef struct {
    int *dados;         // Vetor que armazena os elementos.
    int inicio;         // Posição do próximo elemento a sair.
    int fim;            // Posição da próxima inserção.
    int quantidade;     // Número atual de elementos.
    int capacidade;     // Capacidade máxima da fila.
} Fila;

/* Inicializa a fila e reserva memória para sua capacidade.
*/
int fila_iniciar(Fila *f, int capacidade); // Retorna 1 em caso de sucesso ou 0 em caso de falha.

/* Insere um elemento no final da fila.
*/
int fila_enfileirar(Fila *f, int valor); // Retorna 1 em caso de sucesso ou 0 se estiver cheia ou inválida.

/* Remove o primeiro elemento e o devolve por meio de valor.
*/
int fila_desenfileirar(Fila *f, int *valor); // Retorna 1 em caso de sucesso ou 0 se estiver vazia ou inválida.

/* Exibe os elementos na ordem de saída.
*/
void fila_imprimir(const Fila *f);

/* Libera a memória utilizada pela fila.
*/
void fila_liberar(Fila *f);


/* ÁRVORE BINÁRIA DE BUSCA */

/* Cada nó possui um valor inteiro e ponteiros para as subárvores esquerda e direita.
Regra de organização:
valores menores ficam à esquerda;
valores maiores ficam à direita.
Valores duplicados não são inseridos novamente.
*/
typedef struct NoArvore {
    int valor;              // Valor armazenado no nó.
    struct NoArvore *esq;   // Filho esquerdo.
    struct NoArvore *dir;   // Filho direito.
} NoArvore;

/* Insere um valor na árvore.
*/
int arvore_inserir(NoArvore **raiz, int valor); // Retorna 1 se a operação for aceita ou 0 em caso de falha.

/* Procura um valor e contabiliza os nós examinados.
*/
int arvore_buscar(const NoArvore *raiz, int valor,
                  long long *iteracoes); // Retorna 1 se encontrar ou 0 caso contrário.

/* Exibe os valores em ordem crescente.
*/
void arvore_em_ordem(const NoArvore *raiz);

/* Libera todos os nós da árvore.
*/
void arvore_liberar(NoArvore *raiz);


/* TABELA HASH COM ENCADEAMENTO */

/* A tabela utiliza uma quantidade fixa de posições.
Cada posição pode armazenar uma lista de nós para tratar chaves direcionadas ao mesmo índice.
*/
#define HASH_CAPACIDADE 101

typedef struct NoHash {
    int chave;              // Chave armazenada.
    struct NoHash *prox;    // Próximo nó da lista.
} NoHash;

/* Inicializa todas as posições da tabela como vazias.
*/
void hash_iniciar(NoHash *tabela[HASH_CAPACIDADE]);

/* Insere uma chave na tabela.
*/
int hash_inserir(NoHash *tabela[HASH_CAPACIDADE], int chave); // Retorna 1 se a operação for aceita ou 0 em caso de falha.

/* Procura uma chave e contabiliza os nós examinados.
*/
int hash_buscar(NoHash *tabela[HASH_CAPACIDADE],
                int chave, long long *iteracoes); // Retorna 1 se encontrar ou 0 caso contrário.

/* Exibe as posições ocupadas e suas listas de nós.
*/
void hash_imprimir(NoHash *tabela[HASH_CAPACIDADE]);

/* Libera todos os nós da tabela.
*/
void hash_liberar(NoHash *tabela[HASH_CAPACIDADE]);

#endif
