#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "vetor.h"
#include "ordenacao.h"
#include "busca.h"
#include "metricas.h"
#include "estruturas.h"

/* Configurações gerais do programa.
REPETICOES define quantas vezes cada algoritmo será executado
para calcular uma média de desempenho.
QTD_ALGORITMOS representa a quantidade de algoritmos cadastrados.
*/
#define REPETICOES 5
#define QTD_ALGORITMOS 5

/* Associa o nome de um algoritmo à sua respectiva função de ordenação. */
typedef struct {
    const char *nome;
    FuncaoOrdenacao funcao;
} Algoritmo;

// Cadastro dos algoritmos disponíveis no programa.
static const Algoritmo algoritmos[QTD_ALGORITMOS] = {
    {"Bubble", bubble_sort},
    {"Selection", selection_sort},
    {"Insertion", insertion_sort},
    {"Merge", merge_sort},
    {"Quick", quick_sort}
};

// Indica se a entrada padrão foi encerrada (EOF).
static int entrada_encerrada = 0;


/* FUNÇÕES AUXILIARES DE ENTRADA */

/* Descarta os caracteres restantes da entrada até encontrar
uma quebra de linha ou o final da entrada.

Evita que caracteres inválidos prejudiquem a próxima leitura.
*/
static void limpar_entrada(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
        // Descarta os caracteres restantes.
    }
}

/* Lê um número inteiro informado pelo usuário.

Enquanto a entrada for inválida, solicita um novo valor.

Retorna 0 quando a entrada é encerrada (EOF).
A variável entrada_encerrada diferencia essa situação
de uma escolha normal igual a zero.
*/
static int ler_int(const char *mensagem) {
    int valor;

    for (;;) {
        printf("%s", mensagem);

        if (scanf("%d", &valor) == 1) {
            limpar_entrada();
            return valor;
        }

        // Verifica se a entrada foi encerrada.
        if (feof(stdin)) {
            entrada_encerrada = 1;
            return 0;
        }

        puts("Entrada invalida. Informe um numero inteiro.");

        limpar_entrada();
    }
}


/* EXECUÇÃO DE UM ALGORITMO DE ORDENAÇÃO */

/* Executa o algoritmo escolhido e registra suas métricas.

Cada execução utiliza uma cópia do vetor-base para garantir
que todos os algoritmos recebam os mesmos dados originais.

Quando passo == 1, realiza somente uma execução,
permitindo acompanhar o algoritmo passo a passo.

Quando passo == 0, realiza REPETICOES execuções
e calcula a média das métricas.

Retorna 1 se a execução for concluída com sucesso
ou 0 se ocorrer alguma falha.
*/
static int executar_algoritmo(const int *base, int n,
                              int indice, Metricas *saida, int passo) {

    long long soma_comp = 0;
    long long soma_trocas = 0;
    long long soma_movimentacoes = 0;

    double soma_tempo = 0.0;

    // Define a quantidade de execuções.
    int repeticoes = passo ? 1 : REPETICOES;

    // Inicializa as métricas do resultado.
    metricas_zerar(saida);

    // Ativa ou desativa a exibição passo a passo.
    ordenacao_passo_configurar(passo);

    for (int r = 0; r < repeticoes; r++) {

        // Cria uma cópia do vetor original para cada execução.
        int *copia = vetor_criar(n);

        if (!copia) {
            ordenacao_passo_configurar(0);
            return 0;
        }

        // Copia os dados originais para evitar interferência entre execuções.
        vetor_copiar(copia, base, n);

        // Inicializa as métricas individuais desta execução.
        Metricas atual;
        metricas_zerar(&atual);

        // Marca o início da medição de tempo.
        clock_t ini = clock();

        // Executa o algoritmo selecionado.
        int sucesso = algoritmos[indice].funcao(copia, n, &atual);

        // Marca o fim da medição de tempo.
        clock_t fim = clock();

        if (!sucesso) {
            fprintf(stderr, "Falha durante a execucao de %s.\n",
                    algoritmos[indice].nome);

            free(copia);
            ordenacao_passo_configurar(0);
            return 0;
        }

        // Verifica se o algoritmo realmente ordenou o vetor.
        if (!vetor_ordenado(copia, n)) {
            fprintf(stderr, "Falha: %s nao ordenou corretamente.\n",
                    atual.nome);

            free(copia);
            ordenacao_passo_configurar(0);
            return 0;
        }

        // Acumula as métricas da execução atual.
        soma_comp += atual.comparacoes;
        soma_trocas += atual.trocas;
        soma_movimentacoes += atual.movimentacoes;

        // Converte o tempo medido para milissegundos.
        soma_tempo += (double)(fim - ini) / CLOCKS_PER_SEC * 1000.0;

        // Guarda o nome do algoritmo executado.
        strcpy(saida->nome, atual.nome);

        // Libera a cópia antes da próxima repetição.
        free(copia);
    }

    // Desativa a exibição passo a passo.
    ordenacao_passo_configurar(0);

    // Calcula as médias das métricas inteiras com arredondamento.
    saida->comparacoes =
        (soma_comp + repeticoes / 2) / repeticoes;

    saida->trocas =
        (soma_trocas + repeticoes / 2) / repeticoes;

    saida->movimentacoes =
        (soma_movimentacoes + repeticoes / 2) / repeticoes;

    // No modo passo a passo, o tempo não é apresentado como medição comparável.
    saida->tempo_ms = passo ? 0.0 : soma_tempo / repeticoes;

    return 1;
}


/* MENU DE ORDENAÇÃO */

/* Permite ao usuário escolher um algoritmo específico.

O vetor-base é preservado porque a função de execução
trabalha sempre com uma cópia dos dados.
*/
static void menu_ordenacao(const int *base, int n, TipoDados tipo) {

    puts("\n1-Bubble  2-Selection  3-Insertion  4-Merge  5-Quick");

    int op = ler_int("Algoritmo: ");

    if (entrada_encerrada) return;

    // Verifica se a opção corresponde a um algoritmo válido.
    if (op < 1 || op > QTD_ALGORITMOS) {
        puts("Opcao invalida.");
        return;
    }

    int passo = 0;

    // Permite a exibição passo a passo somente para conjuntos pequenos.
    if (n <= 20) {
        passo = ler_int("Passo a passo? (1=sim, 0=nao): ");

        if (entrada_encerrada) return;

        if (passo != 0 && passo != 1) {
            puts("Opcao invalida.");
            return;
        }
    } else {
        puts("Passo a passo desabilitado para n > 20.");
    }

    Metricas m;

    // Executa o algoritmo e apresenta seu relatório.
    if (executar_algoritmo(base, n, op - 1, &m, passo)) {
        metricas_relatorio(&m, n, vetor_nome_tipo(tipo));
    } else {
        puts("Nao foi possivel concluir a ordenacao.");
    }
}


/* COMPARAÇÃO DE TODOS OS ALGORITMOS */

/* Executa todos os algoritmos cadastrados utilizando
o mesmo vetor-base.

Cada algoritmo recebe sua própria cópia dos dados,
permitindo uma comparação mais justa.
*/
static void menu_todos(const int *base, int n, TipoDados tipo) {

    Metricas resultados[QTD_ALGORITMOS];

    for (int i = 0; i < QTD_ALGORITMOS; i++) {

        printf("Executando %s...\n", algoritmos[i].nome);

        // Interrompe a comparação se algum algoritmo falhar.
        if (!executar_algoritmo(base, n, i, &resultados[i], 0)) {
            puts("Comparacao interrompida.");
            return;
        }
    }

    // Apresenta os resultados de todos os algoritmos.
    metricas_tabela(resultados, QTD_ALGORITMOS,
                    n, vetor_nome_tipo(tipo));
}


/* MENU DE BUSCAS */

/* Permite executar um dos algoritmos de busca.

A busca binária e a busca por interpolação exigem
que o vetor esteja ordenado.
*/
static void menu_busca(const int *v, int n) {

    puts("\n1-Sequencial  2-Binaria iterativa");
    puts("3-Binaria recursiva  4-Interpolacao");

    int op = ler_int("Busca: ");

    if (entrada_encerrada) return;

    if (op < 1 || op > 4) {
        puts("Opcao invalida.");
        return;
    }

    // A busca sequencial não exige ordenação.
    // As demais verificam se o vetor está ordenado.
    if (op != 1 && !vetor_ordenado(v, n)) {
        puts("Busca selecionada exige vetor ordenado.");
        puts("Gere dados ordenados ou ordene uma copia.");
        return;
    }

    int chave = ler_int("Valor procurado: ");

    if (entrada_encerrada) return;

    // Contabiliza as iterações realizadas durante a busca.
    long long it = 0;
    int pos = -1;

    // Seleciona e executa o algoritmo escolhido.
    if (op == 1) {
        pos = busca_sequencial(v, n, chave, &it);

    } else if (op == 2) {
        pos = busca_binaria_iterativa(v, n, chave, &it);

    } else if (op == 3) {
        pos = busca_binaria_recursiva(v, 0, n - 1, chave, &it);

    } else {
        pos = busca_interpolacao(v, n, chave, &it);
    }

    // Apresenta o resultado da busca.
    if (pos >= 0) {
        printf("Encontrado na posicao %d.\n", pos);
    } else {
        puts("Valor nao encontrado.");
    }

    printf("Iteracoes: %lld\n", it);
}


/* DEMONSTRAÇÃO DAS ESTRUTURAS DE DADOS */

/* Constrói e demonstra oito estruturas:

Lista estática;
Lista simplesmente encadeada;
Lista duplamente encadeada;
Lista circular simplesmente encadeada;
Pilha;
Fila circular;
Árvore binária de busca;
Tabela hash com encadeamento.

Todas recebem os valores do vetor-base.

Ao final, todas as estruturas são liberadas,
independentemente de a construção ter sido concluída
ou de ter ocorrido alguma falha.
*/
static void menu_estruturas(const int *v, int n) {

    // Inicializa os objetos em estados seguros.
    ListaEstatica lista_estatica = {NULL, 0, 0};

    Lista lista;

    ListaDupla lista_dupla;

    ListaCircular lista_circular;

    Pilha pilha = {NULL, -1, 0};

    Fila fila = {NULL, 0, 0, 0, 0};

    NoArvore *arvore = NULL;

    NoHash *hash[HASH_CAPACIDADE];

    // Inicializa as listas encadeadas.
    lista_iniciar(&lista);
    lista_dupla_iniciar(&lista_dupla);
    lista_circular_iniciar(&lista_circular);

    // Inicializa as posições da tabela hash como vazias.
    hash_iniciar(hash);

    // Inicializa a lista estática e verifica a alocação.
    if (!lista_estatica_iniciar(&lista_estatica, n)) {
        puts("Falha ao inicializar a lista estatica.");
        goto finalizar;
    }

    // Inicializa a pilha e verifica a alocação.
    if (!pilha_iniciar(&pilha, n)) {
        puts("Falha ao inicializar a pilha.");
        goto finalizar;
    }

    // Inicializa a fila e verifica a alocação.
    if (!fila_iniciar(&fila, n)) {
        puts("Falha ao inicializar a fila.");
        goto finalizar;
    }

    int sucesso = 1;

    // Insere cada elemento do vetor-base nas estruturas.
    for (int i = 0; i < n; i++) {

        /*
        As listas estáticas e circulares recebem os elementos no final.
        As listas simplesmente e duplamente encadeadas recebem no início.
        As demais estruturas mantêm seus comportamentos de inserção.
        O operador || interrompe as inserções após a primeira falha.
        */
        if (!lista_estatica_inserir(&lista_estatica, v[i]) ||
            !lista_inserir(&lista, v[i]) ||
            !lista_dupla_inserir(&lista_dupla, v[i]) ||
            !lista_circular_inserir(&lista_circular, v[i]) ||
            !pilha_push(&pilha, v[i]) ||
            !fila_enfileirar(&fila, v[i]) ||
            !arvore_inserir(&arvore, v[i]) ||
            !hash_inserir(hash, v[i])) {

            sucesso = 0;
            break;
        }
    }

    // Não apresenta estruturas parcialmente preenchidas.
    if (!sucesso) {
        puts("Falha ao construir as estruturas de dados.");
        goto finalizar;
    }

    // Apresenta o conteúdo de cada estrutura.
    puts("\nEstruturas construidas a partir do vetor-base:");

    lista_estatica_imprimir(&lista_estatica);

    lista_imprimir(&lista);

    lista_dupla_imprimir(&lista_dupla);
    lista_dupla_imprimir_reversa(&lista_dupla);

    lista_circular_imprimir(&lista_circular);

    pilha_imprimir(&pilha);

    fila_imprimir(&fila);

    printf("Arvore binaria de busca (percurso em ordem): ");
    arvore_em_ordem(arvore);
    puts("");

    puts("Tabela hash (encadeamento):");
    hash_imprimir(hash);

    // Solicita um valor para consultar nas estruturas.
    puts("\nConsulta nas estruturas:");

    int chave = ler_int("Valor para buscar: ");

    if (entrada_encerrada) {
        goto finalizar;
    }

    long long it = 0;

    // Cada função de busca reinicializa o contador antes da execução.

    // Busca na lista estática.
    printf("Lista estatica: %s",
           lista_estatica_buscar(&lista_estatica, chave, &it) ?
           "encontrado" : "nao encontrado");

    printf(" (%lld posicoes examinadas)\n", it);

    // Busca na lista simplesmente encadeada.
    printf("Lista simples: %s",
           lista_buscar(&lista, chave, &it) ?
           "encontrado" : "nao encontrado");

    printf(" (%lld nos visitados)\n", it);

    // Busca na lista duplamente encadeada.
    printf("Lista dupla: %s",
           lista_dupla_buscar(&lista_dupla, chave, &it) ?
           "encontrado" : "nao encontrado");

    printf(" (%lld nos visitados)\n", it);

    // Busca na lista circular simplesmente encadeada.
    printf("Lista circular: %s",
           lista_circular_buscar(&lista_circular, chave, &it) ?
           "encontrado" : "nao encontrado");

    printf(" (%lld nos visitados)\n", it);

    // Busca na árvore binária de busca.
    printf("Arvore: %s",
           arvore_buscar(arvore, chave, &it) ?
           "encontrado" : "nao encontrado");

    printf(" (%lld nos visitados)\n", it);

    // Busca na tabela hash.
    printf("Hash: %s",
           hash_buscar(hash, chave, &it) ?
           "encontrado" : "nao encontrado");

    printf(" (%lld nos visitados)\n", it);

    // Demonstra operações de remoção nas listas.
    puts("\nRemocao nas listas:");

    printf("Lista estatica: %s\n",
           lista_estatica_remover(&lista_estatica, chave) ?
           "elemento removido" : "valor nao encontrado");

    printf("Lista simples: %s\n",
           lista_remover(&lista, chave) ?
           "elemento removido" : "valor nao encontrado");

    printf("Lista dupla: %s\n",
           lista_dupla_remover(&lista_dupla, chave) ?
           "elemento removido" : "valor nao encontrado");

    printf("Lista circular: %s\n",
           lista_circular_remover(&lista_circular, chave) ?
           "elemento removido" : "valor nao encontrado");

    // Remove o elemento do topo da pilha e o primeiro elemento da fila.
    int valor;

    if (pilha_pop(&pilha, &valor)) {
        printf("Remocao da pilha (pop): %d\n", valor);
    }

    if (fila_desenfileirar(&fila, &valor)) {
        printf("Remocao da fila (desenfileirar): %d\n", valor);
    }

    // Libera todas as estruturas, inclusive em caso de falha.
finalizar:

    lista_estatica_liberar(&lista_estatica);
    lista_liberar(&lista);
    lista_dupla_liberar(&lista_dupla);
    lista_circular_liberar(&lista_circular);

    pilha_liberar(&pilha);
    fila_liberar(&fila);

    arvore_liberar(arvore);
    hash_liberar(hash);
}


/* EXIBIÇÃO DO MENU PRINCIPAL */

/* Apresenta as opções disponíveis para o usuário.

O menu organiza as funcionalidades do programa em três áreas:
geração e visualização de dados, testes de algoritmos
e demonstração de estruturas de dados.

Os números das opções correspondem aos cases da função main().
*/
static void exibir_menu(void) {

    puts("\n==================================================");
    puts("   TESTES DE ALGORITMOS E ESTRUTURAS DE DADOS");
    puts("==================================================");

    puts("\n--- CONJUNTO DE DADOS ---");
    puts("1 - Gerar conjunto de dados");
    puts("2 - Exibir conjunto de dados");

    puts("\n--- ALGORITMOS DE ORDENACAO ---");
    puts("3 - Executar uma ordenacao");
    puts("4 - Comparar todos os algoritmos de ordenacao");

    puts("\n--- PESQUISA ---");
    puts("5 - Executar busca");

    puts("\n--- ESTRUTURAS DE DADOS ---");
    puts("6 - Demonstrar estruturas de dados");
    
    puts("\n0 - Sair");

    puts("==================================================");
}


/* FUNÇÃO PRINCIPAL */

/* Controla o fluxo geral do programa.

Mantém o vetor-base durante toda a execução.
Os algoritmos de ordenação trabalham com cópias,
preservando os dados utilizados pelas buscas
e pelas demonstrações das estruturas.
*/
int main(void) {

    // Inicializa a semente para geração de números aleatórios.
    srand((unsigned)time(NULL));

    // Inicialmente, nenhum vetor foi criado.
    int *base = NULL;
    int n = 0;

    // Guarda o tipo de conjunto de dados atualmente utilizado.
    TipoDados tipo = DADOS_ALEATORIOS;

    int op;

    do {

        exibir_menu();

        op = ler_int("Opcao: ");

        // Finaliza o programa se a entrada for encerrada.
        if (entrada_encerrada) {
            op = 0;
        }

        switch (op) {

            /* OPÇÃO 1: CRIAR OU GERAR CONJUNTO DE DADOS */
            case 1: {

                int tamanho;

                // Solicita uma quantidade positiva de elementos.
                do {
                    tamanho = ler_int(
                        "Quantidade de elementos (n > 0): "
                    );

                    if (entrada_encerrada) {
                        break;
                    }

                    if (tamanho <= 0) {
                        puts("O tamanho deve ser positivo.");
                    }

                } while (tamanho <= 0);

                if (entrada_encerrada) {
                    break;
                }

                // Solicita o tipo de conjunto de dados.
                puts("1-Aleatorio  2-Ordenado  3-Invertido");

                int t = ler_int("Tipo: ");

                if (entrada_encerrada) {
                    break;
                }

                if (t < 1 || t > 3) {
                    puts("Tipo invalido.");
                    break;
                }

                // Cria o novo vetor antes de liberar o anterior.
                // Assim, o conjunto atual é preservado se a alocação falhar.
                int *novo = vetor_criar(tamanho);

                if (!novo) {
                    puts("Falha na alocacao.");
                    break;
                }

                // Converte a opção para o tipo definido em vetor.h.
                tipo = (TipoDados)t;

                // Gera os dados conforme o tipo selecionado.
                vetor_gerar(novo, tamanho, tipo);

                // Libera o conjunto anterior, se existir.
                free(base);

                // Atualiza o vetor-base e sua quantidade de elementos.
                base = novo;
                n = tamanho;

                printf("Conjunto criado: %d elementos (%s).\n",
                       n, vetor_nome_tipo(tipo));

                // Exibe automaticamente conjuntos pequenos.
                if (n <= 30) {
                    vetor_imprimir(base, n);
                }

                break;
            }

            /* OPÇÃO 2: EXIBIR CONJUNTO DE DADOS */
            case 2:

                if (!base) {
                    puts("Crie um conjunto primeiro.");
                } else {
                    vetor_imprimir(base, n);
                }

                break;

            /* OPÇÃO 3: EXECUTAR UMA ORDENAÇÃO */
            case 3:

                if (!base) {
                    puts("Crie um conjunto primeiro.");
                } else {
                    menu_ordenacao(base, n, tipo);
                }

                break;

            /* OPÇÃO 4: COMPARAR TODOS OS ALGORITMOS */
            case 4:

                if (!base) {
                    puts("Crie um conjunto primeiro.");
                } else {
                    menu_todos(base, n, tipo);
                }

                break;

            /* OPÇÃO 5: EXECUTAR UMA BUSCA */
            case 5:

                if (!base) {
                    puts("Crie um conjunto primeiro.");
                } else {
                    menu_busca(base, n);
                }

                break;

            /* OPÇÃO 6: DEMONSTRAR ESTRUTURAS DE DADOS */
            case 6:

                if (!base) {
                    puts("Crie um conjunto primeiro.");
                } else {
                    menu_estruturas(base, n);
                }

                break;

            /* OPÇÃO 0: ENCERRAR O PROGRAMA */
            case 0:

                puts("Programa encerrado.");
                break;

            // Trata qualquer opção diferente das disponíveis.
            default:

                puts("Opcao invalida.");
        }

    } while (op != 0 && !entrada_encerrada);

    // Libera o vetor-base antes de encerrar.
    // As demais estruturas e cópias são liberadas em suas próprias funções.
    free(base);

    return 0;
}
