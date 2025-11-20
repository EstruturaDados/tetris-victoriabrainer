#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// -------------------------------
// Definições
// -------------------------------

#define TAM_FILA 5
#define TAM_PILHA 3

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

// 🧠 Nível Aventureiro: Adição da Pilha de Reserva
//
// - Implemente uma pilha linear com capacidade para 3 peças.
// - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
// - Permita enviar uma peça da fila para a pilha (reserva).
// - Crie um menu com opção:
//      2 - Enviar peça da fila para a reserva (pilha)
//      3 - Usar peça da reserva (remover do topo da pilha)
// - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
// - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


// ============================================================================
// Struct
// ============================================================================
typedef struct {
    char nome;  // I, O, T, L
    int id;     // identificador único
} Peca;

// ============================================================================
// Variáveis globais da fila
// ============================================================================

Peca fila[TAM_FILA];
int frente = 0;
int tras = 0;
int contadorFila = 0;

// ============================================================================
// Variáveis globais da pilha
// ============================================================================

Peca pilha[TAM_PILHA];
int topo = -1;

// Contador global para IDs
int idGlobal = 0;


// ============================================================================
// Protótipos das funções
// ============================================================================
void limparBuffer();

char gerarNomePeca();
Peca gerarPeca();
int filaCheia();
int filaVazia();
void inicializarFila();
Peca dequeue();
void enqueue(Peca p);

void inicializarPilha();
int pilhaVazia();
int pilhaCheia();
void push(Peca p);
Peca pop();

void mostrarEstado();
void menu();

// ============================================================================
// Função principal
// ============================================================================

int main() {
    srand(time(NULL));

    inicializarFila();
    inicializarPilha();

    int opcao;

    do {
        mostrarEstado();
        menu();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: {
                // Jogar peça
                Peca jogada = dequeue();
                if (jogada.id != -1) {
                    printf("Peca jogada: [%c %d]\n", jogada.nome, jogada.id);
                    enqueue(gerarPeca());
                }
                break;
            }

            case 2: {
                // Reservar peça
                if (pilhaCheia()) {
                    printf("Nao eh possivel reservar. A pilha esta cheia!\n");
                    break;
                }
                Peca reservada = dequeue();
                if (reservada.id != -1) {
                    push(reservada);
                    printf("Peca reservada: [%c %d]\n", reservada.nome, reservada.id);
                    enqueue(gerarPeca());
                }
                break;
            }

            case 3: {
                // Usar peça reservada
                Peca usada = pop();
                if (usada.id != -1) {
                    printf("Peca usada da reserva: [%c %d]\n", usada.nome, usada.id);
                }
                break;
            }

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}

// ============================================================================
// Funções Auxiliares
// ============================================================================

/**
 * @brief Limpa o buffer do teclado.
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Gera um nome aleatório para a peça.
 * @return char Nome da peça.
 */
char gerarNomePeca() {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    return tipos[rand() % 4];
}


/**
 * @brief Gera uma nova peça com nome aleatório e id único.
 * @return Peca Nova peça gerada.
 */
Peca gerarPeca() {
    Peca p;
    p.nome = gerarNomePeca();
    p.id = idGlobal++;
    return p;
}

// ============================================================================
// FILA
// ============================================================================


/**
 * @brief Inicializa a fila com peças geradas.
 */
void inicializarFila() {
    for (int i = 0; i < TAM_FILA; i++) {
        fila[i] = gerarPeca();
        tras = (tras + 1) % TAM_FILA;
        contadorFila++;
    }
}


/** 
 * @brief Verifica se a fila está vazia.
 * @return int 1 se vazia, 0 caso contrário.
 */
int filaVazia() {
    return contadorFila == 0;
}


/** 
 * @brief Verifica se a fila está cheia.
 * @return int 1 se cheia, 0 caso contrário.
 */
int filaCheia() {
    return contadorFila == TAM_FILA;
}


/**
 * @brief Remove a peça da frente da fila.
 * @return Peca Peça removida.
 */
Peca dequeue() {
    if (filaVazia()) {
        printf("Fila vazia! Nao eh possivel jogar peca.\n");
        Peca vazio = {'-', -1};
        return vazio;
    }

    Peca removida = fila[frente];
    frente = (frente + 1) % TAM_FILA;
    contadorFila--;

    return removida;
}


/**
 * @brief Insere uma nova peça na fila.
 * @param p Peça a ser inserida.
 */
void enqueue(Peca p) {
    if (filaCheia()) {
        printf("ERRO: fila cheia!\n");
        return;
    }

    fila[tras] = p;
    tras = (tras + 1) % TAM_FILA;
    contadorFila++;
}

// ============================================================================
// PILHA
// ============================================================================

/**
 * @brief Inicializa a pilha.
 */
void inicializarPilha() {
    topo = -1;
}


/**
 * @brief Verifica se a pilha está vazia.
 * @return int 1 se vazia, 0 caso contrário.
 */
int pilhaVazia() {
    return topo == -1;
}


/**
 * @brief Verifica se a pilha está cheia.
 * @return int 1 se cheia, 0 caso contrário.
 */
int pilhaCheia() {
    return topo == TAM_PILHA - 1;
}


/**
 * @brief Adiciona uma peça no topo da pilha.
 * @param p Peça a ser adicionada.
 */
void push(Peca p) {
    if (pilhaCheia()) {
        printf("Pilha cheia! Nao eh possivel reservar.\n");
        return;
    }

    pilha[++topo] = p;
}


/**
 * @brief Remove e retorna a peça do topo da pilha.
 * @return Peca Peça removida.
 */
Peca pop() {
    if (pilhaVazia()) {
        printf("Pilha vazia! Nada para usar.\n");
        Peca vazio = {'-', -1};
        return vazio;
    }

    return pilha[topo--];
}

// ============================================================================
// Exibição
// ============================================================================

/**
 * @brief Exibe o estado atual da fila e da pilha.
 */
void mostrarEstado() {
    printf("\n=== Estado Atual ===\n");

    printf("Fila de Pecas:\t");
    int i = frente;
    for (int c = 0; c < contadorFila; c++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");

    printf("Pilha de Reserva (Topo -> Base): ");
    if (pilhaVazia()) {
        printf("(vazia)");
    } else {
        for (int i = topo; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
    }

    printf("\n=====================\n");
}


/**
 * @brief Exibe o menu principal do jogo.
 */
void menu() {
    printf("\n=== MENU ===\n");
    printf("1 - Jogar peca da fila\n");
    printf("2 - Reservar peca (enviar da fila para a pilha)\n");
    printf("3 - Usar peca reservada (remover do topo da pilha)\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
}
