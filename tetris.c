#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5  // tamanho fixo da fila
#define TAM_PILHA 3 // capacidade da pilha de reserva

// --- Struct da peça ---
typedef struct
{
    char nome; // tipo da peça ('I', 'O', 'T', 'L')
    int id;    // identificador único e sequencial
} Peca;

// --- Struct da fila circular ---
typedef struct
{
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// --- Struct da pilha linear ---
typedef struct
{
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

// --- Inicializa a fila ---
void InicializarFila(Fila *f)
{
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

// --- Inicializa a pilha ---
void InicializarPilha(Pilha *p)
{
    p->topo = -1;
}

// --- Verificações da pilha ---
int PilhaVazia(Pilha *p)
{
    return p->topo == -1;
}

int PilhaCheia(Pilha *p)
{
    return p->topo == TAM_PILHA - 1;
}

// --- Gerar nova peça com ID sequencial ---
Peca gerarPeca()
{
    static int nextId = 0; // mantém o ID entre chamadas
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = nextId++;
    return nova;
}

// --- Inserir nova peça no fim da fila (enqueue) ---
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
}

// --- Remover peça da frente da fila (dequeue) ---
Peca RemoverPeca(Fila *f)
{
    Peca removida = {'?', -1};
    if (f->quantidade == 0)
    {
        printf("Fila vazia! Nenhuma peça para remover.\n");
        return removida;
    }

    removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return removida;
}

// --- Empilhar peça (push) ---
void Push(Pilha *p, Peca x)
{
    if (PilhaCheia(p))
    {
        printf("Pilha cheia! Não é possível reservar nova peça.\n");
        return;
    }
    p->itens[++(p->topo)] = x;
}

// --- Desempilhar peça (pop) ---
Peca Pop(Pilha *p)
{
    Peca removida = {'?', -1};
    if (PilhaVazia(p))
    {
        printf("Pilha vazia! Nenhuma peça reservada para usar.\n");
        return removida;
    }
    removida = p->itens[(p->topo)--];
    return removida;
}

// --- Exibir fila ---
void ExibirFila(Fila *f)
{
    printf("\nFila de peças: ");
    if (f->quantidade == 0)
    {
        printf("[vazia]");
    }
    else
    {
        for (int i = 0; i < f->quantidade; i++)
        {
            int idx = (f->inicio + i) % TAM_FILA;
            printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
        }
    }
    printf("\n");
}

// --- Exibir pilha ---
void ExibirPilha(Pilha *p)
{
    printf("Pilha de reserva (Topo -> Base): ");
    if (PilhaVazia(p))
    {
        printf("[vazia]");
    }
    else
    {
        for (int i = p->topo; i >= 0; i--)
        {
            printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
        }
    }
    printf("\n");
}

// --- Exibir estado geral ---
void ExibirEstado(Fila *f, Pilha *p)
{
    printf("\n=== Estado Atual ===\n");
    ExibirFila(f);
    ExibirPilha(p);
    printf("=====================\n");
}

// --- Programa principal ---
int main()
{
    srand(time(NULL));

    Fila fila;
    Pilha pilha;
    InicializarFila(&fila);
    InicializarPilha(&pilha);

    // Preenche fila inicial com 5 peças
    for (int i = 0; i < TAM_FILA; i++)
    {
        InserirPeca(&fila, gerarPeca());
    }

    int opcao;
    do
    {
        ExibirEstado(&fila, &pilha);

        printf("\n--- Menu ---\n");
        printf("1 - Jogar peça\n");
        printf("2 - Inserir nova peça manualmente\n");
        printf("3 - Reservar peça (mover da fila -> pilha)\n");
        printf("4 - Usar peça reservada (retirar da pilha)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            Peca jogada = RemoverPeca(&fila);
            if (jogada.id != -1)
            {
                printf("Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
                InserirPeca(&fila, gerarPeca()); // mantém fila cheia
            }
            break;
        }
        case 2:
            InserirPeca(&fila, gerarPeca());
            break;

        case 3:
        {
            Peca frente = RemoverPeca(&fila);
            if (frente.id != -1)
            {
                Push(&pilha, frente);
                printf("Peça reservada: [%c %d]\n", frente.nome, frente.id);
                InserirPeca(&fila, gerarPeca()); // mantém fila cheia
            }
            break;
        }

        case 4:
        {
            Peca usada = Pop(&pilha);
            if (usada.id != -1)
            {
                printf("Peça usada da reserva: [%c %d]\n", usada.nome, usada.id);
            }
            break;
        }

        case 0:
            printf("Encerrando o programa...\n");
            break;

        default:
            printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
