#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

// 🧩 Nível Novato: Fila de Peças Futuras
//
// - Crie uma struct Peca com os campos: tipo (char) e id (int).
// - Implemente uma fila circular com capacidade para 5 peças.
// - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
// - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
// - Exiba a fila após cada ação com uma função mostrarFila().
// - Use um menu com opções como:
//      1 - Jogar peça (remover da frente)
//      0 - Sair
// - A cada remoção, insira uma nova peça ao final da fila.


// ============================================================================
// Struct
// ============================================================================
/**
 * @brief Estrutura que representa uma peça futura do Tetris Stack.
 */
typedef struct {
    char nome;   ///< Tipo da peça ('I', 'O', 'T', 'L')
    int id;      ///< Identificador único da peça
} Peca;

// ============================================================================
// Variáveis globais de controle da fila circular
// ============================================================================
int inicio = 0;        ///< Índice do primeiro elemento da fila
int fim = 0;           ///< Índice da próxima posição de inserção
int quantidade = 0;    ///< Quantidade atual de peças na fila
int proximoId = 0;     ///< Contador global para IDs únicos

// ============================================================================
// Protótipos das funções
// ============================================================================
Peca gerarPeca();
int filaCheia();
int filaVazia();
void enqueue(Peca fila[]);
void dequeue(Peca fila[]);
void mostrarFila(Peca fila[]);
void menu();
void inicializarFila(Peca fila[]);
void limparBuffer();


// ============================================================================
// MAIN
// ============================================================================
int main() {
    srand(time(NULL));

    Peca fila[TAM_FILA];

    inicializarFila(fila);

    int opcao;

    do {
        mostrarFila(fila);
        menu();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                dequeue(fila);
                break;

            case 2:
                enqueue(fila);
                break;

            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}


/**
 * @brief Gera uma nova peça com nome aleatório e id único.
 * @return Peca Nova peça gerada.
 */
Peca gerarPeca() {
    char tipos[] = { 'I', 'O', 'T', 'L' };
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = proximoId++;
    return nova;
}


/**
 * @brief Verifica se a fila está cheia.
 * @return int 1 se cheia, 0 caso contrário.
 */
int filaCheia() {
    return quantidade == TAM_FILA;
}


/**
 * @brief Verifica se a fila está vazia.
 * @return int 1 se vazia, 0 caso contrário.
 */
int filaVazia() {
    return quantidade == 0;
}


/**
 * @brief Insere uma nova peça na fila circular.
 * @param fila Vetor que representa a fila de peças.
 */
void enqueue(Peca fila[]) {
    if (filaCheia()) {
        printf("\nFila cheia! Nao eh possivel inserir nova peca.\n");
        return;
    }

    fila[fim] = gerarPeca();
    fim = (fim + 1) % TAM_FILA;
    quantidade++;

    printf("\nPeca [%c %d] adicionada ao final da fila!\n",
           fila[(fim - 1 + TAM_FILA) % TAM_FILA].nome,
           fila[(fim - 1 + TAM_FILA) % TAM_FILA].id);
}


/**
 * @brief Remove a peça da frente da fila.
 * @param fila Vetor que representa a fila de peças.
 */
void dequeue(Peca fila[]) {
    if (filaVazia()) {
        printf("\nFila vazia! Nenhuma peca para jogar.\n");
        return;
    }

    Peca removida = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    quantidade--;

    printf("\nPeca jogada: [%c %d]\n", removida.nome, removida.id);
}


/**
 * @brief Exibe o estado atual da fila circular de peças.
 * @param fila Vetor que representa a fila.
 */
void mostrarFila(Peca fila[]) {
    printf("\n=== Fila de Pecas ===\n");

    if (filaVazia()) {
        printf("(fila vazia)\n");
        return;
    }

    int idx = inicio;

    for (int i = 0; i < quantidade; i++) {
        printf("[%c %d] ", fila[idx].nome, fila[idx].id);
        idx = (idx + 1) % TAM_FILA;
    }

    printf("\n");
}


// ============================================================================
// Funções Auxiliares
// ============================================================================
/**
 * @brief Exibe o menu principal do jogo.
 */
void menu() {
    printf("\n--- MENU ---\n");
    printf("1. Jogar peca (dequeue)\n");
    printf("2. Inserir nova peca (enqueue)\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}


/**
 * @brief Inicializa a fila com 5 peças.
 */
void inicializarFila(Peca fila[]) {
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(fila);
    }
}


/**
 * @brief Limpa o buffer do teclado.
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}