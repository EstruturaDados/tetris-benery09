#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

// --- Struct da peça ---
typedef struct
{
    char nome;
    int id;
} Peca;

// --- Struct da fila ---
typedef struct
{
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// --- Inicializar fila ---
void InicializarFila(Fila *f)
{
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

// --- Gerar peça ---
Peca gerarPeca()
{
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = rand() % 1000;
    return nova;
}

// --- Exibir fila ---
void ExibirFila(Fila *f)
{
    printf("\n--- Fila de Peças ---\n");
    if (f->quantidade == 0)
    {
        printf("[vazia]\n");
        return;
    }
    for (int i = 0; i < f->quantidade; i++)
    {
        int idx = (f->inicio + i) % TAM_FILA;
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\n");
}

// --- Inserir nova peça (enqueue) ---
void InserirPeca(Fila *f, Peca nova)
{
    if (f->quantidade == TAM_FILA)
    {
        printf("Fila cheia! Não é possível inserir nova peça.\n");
        return;
    }

    f->itens[f->fim] = nova;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
    printf("Peça inserida: [%c %d]\n", nova.nome, nova.id);
}

// --- Jogar peça (dequeue) ---
void JogarPeca(Fila *f)
{
    if (f->quantidade == 0)
    {
        printf("Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca jogada = f->itens[f->inicio];
    printf("Peça jogada: [%c %d]\n", jogada.nome, jogada.id);

    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
}

// --- Programa principal ---
int main()
{
    srand(time(NULL));
    Fila fila;
    InicializarFila(&fila);

    // inicializa com 5 peças
    for (int i = 0; i < TAM_FILA; i++)
    {
        InserirPeca(&fila, gerarPeca());
    }

    int opcao;
    do
    {
        ExibirFila(&fila);
        printf("\n--- Menu ---\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("3 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            JogarPeca(&fila);
            break;
        case 2:
            InserirPeca(&fila, gerarPeca());
            break;
        case 3:
            printf("Saindo do jogo...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}
