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

// 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
//
// - Implemente interações avançadas entre as estruturas:
//      4 - Trocar a peça da frente da fila com o topo da pilha
//      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
// - Para a opção 4:
//      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
//      Troque os elementos diretamente nos arrays.
// - Para a opção 5:
//      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
//      Use a lógica de índice circular para acessar os primeiros da fila.
// - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
// - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
// - O menu deve ficar assim:
//      4 - Trocar peça da frente com topo da pilha
//      5 - Trocar 3 primeiros da fila com os 3 da pilha


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
void trocarFrenteComTopo();
void trocarTres();
void inverterFilaComPilha();

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

            case 4: // Trocar frente da fila com topo da pilha
                trocarFrenteComTopo();
                break;

            case 5: // Trocar 3 da fila com 3 da pilha
                trocarTres();
                break;

            case 6: // Inverter fila e pilha
                inverterFilaComPilha();
                break;

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


/**
 * @brief Troca a peça da frente da fila com o topo da pilha.
 */
void trocarFrenteComTopo() {
    if (filaVazia() || pilhaVazia()) {
        printf("Nao eh possivel trocar. A fila ou pilha esta vazia!\n");
        return;
    }

    Peca temp = fila[frente];
    fila[frente] = pilha[topo];
    pilha[topo] = temp;

    printf("Troca realizada entre a frente da fila e o topo da pilha.\n");
}


/**
 * @brief Troca os 3 primeiros da fila com os 3 da pilha.
 */
void trocarTres() {
    if (contadorFila < 3 || topo + 1 < 3) {
        printf("Nao eh possivel trocar. Fila ou pilha nao possuem 3 pecas.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int indiceFila = (frente + i) % TAM_FILA;
        Peca temp = fila[indiceFila];
        fila[indiceFila] = pilha[topo - i];
        pilha[topo - i] = temp;
    }

    printf("Troca realizada entre os 3 primeiros da fila e os 3 da pilha.\n");
}


/**
 * @brief Inverte os elementos da fila com os da pilha.
 */
void inverterFilaComPilha() {
    if (contadorFila != TAM_FILA || topo + 1 != TAM_PILHA) {
        printf("Nao eh possivel inverter. Fila ou pilha estao vazias.\n");
        return;
    }

    for (int i = 0; i < TAM_PILHA; i++) {
        int indiceFila = (frente + i) % TAM_FILA;
        Peca temp = fila[indiceFila];
        fila[indiceFila] = pilha[i];
        pilha[i] = temp;
    }

    printf("Inversao realizada com sucesso entre a fila e a pilha!\n");
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
    printf("4 - Trocar frente da fila com topo da pilha\n");
    printf("5 - Trocar 3 da fila com 3 da pilha\n");
    printf("6 - Inverter fila com pilha\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
}
