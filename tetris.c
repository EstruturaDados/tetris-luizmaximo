#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAM_FILA 5

// Estrutura da peça
typedef struct {
    int id;
    char nome[2];
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca fila[TAM_FILA];
    int frente;
    int tras;
    int total;
} FilaCircular;

// -------------------- Funções --------------------

// Gera uma nova peça automaticamente
Peca gerarPeca(int id) {
    Peca nova;
    nova.id = id;
    char tipos[][2] = {"I", "O", "T", "L", "S", "Z", "J"};
    int n = rand() % 7;
    strcpy(nova.nome, tipos[n]);
    return nova;
}

// Inicializa a fila com 5 peças
void inicializarFila(FilaCircular *f) {
    f->frente = 0;
    f->tras = -1;
    f->total = 0;

    for (int i = 0; i < TAM_FILA; i++) {
        Peca nova = gerarPeca(i + 1);
        f->tras = (f->tras + 1) % TAM_FILA;
        f->fila[f->tras] = nova;
        f->total++;
    }
}

// Verifica se a fila está cheia
int filaCheia(FilaCircular *f) {
    return f->total == TAM_FILA;
}

// Verifica se a fila está vazia
int filaVazia(FilaCircular *f) {
    return f->total == 0;
}

// Remove a peça da frente (jogar)
Peca jogarPeca(FilaCircular *f) {
    Peca removida = f->fila[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->total--;
    return removida;
}

// Insere uma nova peça no final (enqueue)
void inserirPeca(FilaCircular *f, Peca nova) {
    if (filaCheia(f)) {
        printf("A fila está cheia! Não é possível inserir.\n");
        return;
    }
    f->tras = (f->tras + 1) % TAM_FILA;
    f->fila[f->tras] = nova;
    f->total++;
}

// Exibe o estado atual da fila
void exibirFila(FilaCircular *f) {
    printf("\n=== Fila de Peças Futuras ===\n");
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }

    printf("Posição | ID | Tipo\n");
    printf("---------------------\n");
    int i = f->frente;
    for (int c = 0; c < f->total; c++) {
        printf("%7d | %2d |  %s\n", c + 1, f->fila[i].id, f->fila[i].nome);
        i = (i + 1) % TAM_FILA;
    }
}

// -------------------- Programa principal --------------------
int main() {
    FilaCircular fila;
    int idContador = TAM_FILA;
    int opcao;

    srand(time(NULL));
    inicializarFila(&fila);

    do {
        printf("\n=== Menu Tetris Stack - Nível Novato ===\n");
        printf("1 - Jogar peça (remover da frente)\n");
        printf("2 - Inserir nova peça (automática)\n");
        printf("3 - Visualizar fila\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (filaVazia(&fila)) {
                    printf("Nenhuma peça para jogar!\n");
                } else {
                    Peca jogada = jogarPeca(&fila);
                    printf("Peça jogada: %s (ID %d)\n", jogada.nome, jogada.id);

                    // Inserir automaticamente nova peça
                    idContador++;
                    Peca nova = gerarPeca(idContador);
                    inserirPeca(&fila, nova);
                    printf("Nova peça gerada automaticamente: %s (ID %d)\n", nova.nome, nova.id);
                }
                break;

            case 2:
                if (filaCheia(&fila)) {
                    printf("A fila já está cheia!\n");
                } else {
                    idContador++;
                    Peca nova = gerarPeca(idContador);
                    inserirPeca(&fila, nova);
                    printf("Nova peça adicionada: %s (ID %d)\n", nova.nome, nova.id);
                }
                break;

            case 3:
                exibirFila(&fila);
                break;

            case 0:
                printf("Saindo do jogo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
