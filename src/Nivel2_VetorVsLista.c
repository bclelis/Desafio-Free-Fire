/*
 * DESAFIO NÍVEL 2: MOCHILA (VETOR VS. LISTA ENCADEADA)
 * LINGUAGEM: C
 *
 * DESCRIÇÃO: Compara duas implementações de mochila:
 * 1. Vetor (Lista Sequencial): Com ordenação (Bubble Sort) e busca binária.
 * 2. Lista Encadeada (Dinâmica): Com operações padrão.
 * O sistema conta as comparações nas buscas para análise de eficiência.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS_VETOR 20 // Capacidade do vetor

// --- ESTRUTURAS ---

// Nível 2: Struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nível 2: Struct No (para Lista Encadeada)
typedef struct No {
    Item dados;
    struct No* proximo;
} No;


// --- PROTÓTIPOS GERAIS ---
void limparBuffer();
void pausar(); // Para melhor visualização

// --- PROTÓTIPOS - VETOR ---
void menuVetor(Item mochilaVetor[], int* totalVetor);
void inserirItemVetor(Item mochilaVetor[], int* totalVetor);
void removerItemVetor(Item mochilaVetor[], int* totalVetor);
void listarItensVetor(Item mochilaVetor[], int totalVetor);
void buscarSequencialVetor(Item mochilaVetor[], int totalVetor);
void ordenarVetor(Item mochilaVetor[], int totalVetor);
void buscarBinariaVetor(Item mochilaVetor[], int totalVetor, int estaOrdenado);

// --- PROTÓTIPOS - LISTA ENCADEADA ---
void menuLista(No** lista);
void inserirItemLista(No** lista);
void removerItemLista(No** lista);
void listarItensLista(No* lista);
void buscarSequencialLista(No* lista);
void liberarLista(No** lista);


// --- FUNÇÃO PRINCIPAL ---
int main() {
    // Estruturas de dados para as duas versões
    Item mochilaVetor[MAX_ITENS_VETOR];
    int totalVetor = 0;
    int estaOrdenado = 0; // Flag para busca binária

    No* mochilaLista = NULL; // Ponteiro inicial (cabeça) da lista

    int opcao;

    do {
        printf("\n--- NIVEL 2: VETOR VS. LISTA ENCADEADA ---\n");
        printf("1. Gerenciar Mochila (Vetor)\n");
        printf("2. Gerenciar Mochila (Lista Encadeada)\n");
        printf("0. Sair e liberar memoria\n");
        printf("Escolha o modo de operacao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                // Passamos o ponteiro 'estaOrdenado' para que a função menuVetor
                // possa modificar a flag original.
                menuVetor(mochilaVetor, &totalVetor, &estaOrdenado);
                break;
            case 2:
                menuLista(&mochilaLista);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    // Nível 2: Gerenciamento de Memória
    liberarLista(&mochilaLista);
    printf("Memoria da lista encadeada liberada.\n");

    return 0;
}


// --- IMPLEMENTAÇÃO GERAL ---

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar() {
    printf("\nPressione Enter para continuar...");
    limparBuffer();
}

// --- IMPLEMENTAÇÃO - MOCHILA (VETOR) ---

void menuVetor(Item mochilaVetor[], int* totalVetor, int* estaOrdenado) {
    int opcaoVetor = -1;
    do {
        printf("\n--- Mochila (VETOR) | Itens: %d/%d | Ordenado: %s ---\n",
               *totalVetor, MAX_ITENS_VETOR, (*estaOrdenado ? "Sim" : "Nao"));
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar (Sequencial)\n");
        printf("5. Ordenar Vetor (Bubble Sort por Nome)\n");
        printf("6. Buscar (Binaria por Nome)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Opcao: ");
        scanf("%d", &opcaoVetor);
        limparBuffer();

        switch (opcaoVetor) {
            case 1:
                inserirItemVetor(mochilaVetor, totalVetor);
                *estaOrdenado = 0; // Inserção "quebra" a ordenação
                break;
            case 2:
                removerItemVetor(mochilaVetor, totalVetor);
                // A remoção pode ou não quebrar a ordenação,
                // mas por segurança, resetamos.
                *estaOrdenado = 0;
                break;
            case 3:
                listarItensVetor(mochilaVetor, *totalVetor);
                break;
            case 4:
                buscarSequencialVetor(mochilaVetor, *totalVetor);
                break;
            case 5:
                ordenarVetor(mochilaVetor, *totalVetor);
                *estaOrdenado = 1; // Vetor agora está ordenado
                break;
            case 6:
                buscarBinariaVetor(mochilaVetor, *totalVetor, *estaOrdenado);
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
        if(opcaoVetor != 0 && opcaoVetor != 3) pausar();

    } while (opcaoVetor != 0);
}

void inserirItemVetor(Item mochilaVetor[], int* totalVetor) {
    if (*totalVetor >= MAX_ITENS_VETOR) {
        printf("Erro: Mochila (Vetor) cheia!\n");
        return;
    }
    printf("\n[Vetor] Nome do item: ");
    scanf("%29s", mochilaVetor[*totalVetor].nome);
    limparBuffer();
    printf("[Vetor] Tipo do item: ");
    scanf("%19s", mochilaVetor[*totalVetor].tipo);
    limparBuffer();
    printf("[Vetor] Quantidade: ");
    scanf("%d", &mochilaVetor[*totalVetor].quantidade);
    limparBuffer();

    (*totalVetor)++;
    printf("Item adicionado ao vetor.\n");
}

void listarItensVetor(Item mochilaVetor[], int totalVetor) {
    if (totalVetor == 0) {
        printf("\nMochila (Vetor) esta vazia.\n");
        return;
    }
    printf("\n--- Itens no Vetor (%d) ---\n", totalVetor);
    printf("| %-20s | %-15s | %s\n", "Nome", "Tipo", "Qtd.");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < totalVetor; i++) {
        printf("| %-20s | %-15s | %d\n",
               mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
    printf("---------------------------------------------------\n");
}

void removerItemVetor(Item mochilaVetor[], int* totalVetor) {
    if (*totalVetor == 0) {
        printf("\nMochila (Vetor) vazia.\n");
        return;
    }
    char nomeBusca[30];
    printf("\n[Vetor] Nome do item a remover: ");
    scanf("%29s", nomeBusca);
    limparBuffer();

    int indice = -1;
    for (int i = 0; i < *totalVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Item '%s' nao encontrado no vetor.\n", nomeBusca);
        return;
    }

    for (int i = indice; i < (*totalVetor - 1); i++) {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }
    (*totalVetor)--;
    printf("Item '%s' removido do vetor.\n", nomeBusca);
}

void buscarSequencialVetor(Item mochilaVetor[], int totalVetor) {
    if (totalVetor == 0) {
        printf("\nMochila (Vetor) vazia.\n");
        return;
    }
    char nomeBusca[30];
    printf("\n[Vetor] Nome do item (Busca Sequencial): ");
    scanf("%29s", nomeBusca);
    limparBuffer();

    int comparacoes = 0; // Nível 2: Contador de operações
    int indice = -1;

    for (int i = 0; i < totalVetor; i++) {
        comparacoes++; // Conta cada strcmp
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            indice = i;
            break; // Encontrou, para de buscar
        }
    }

    if (indice != -1) {
        printf("Item encontrado!\n");
        printf("  Nome: %s (Tipo: %s, Qtd: %d)\n",
            mochilaVetor[indice].nome, mochilaVetor[indice].tipo, mochilaVetor[indice].quantidade);
    } else {
        printf("Item '%s' nao encontrado.\n", nomeBusca);
    }
    printf("Busca Sequencial (Vetor) realizou %d comparacoes.\n", comparacoes);
}

/**
 * Nível 2: Ordenação no vetor (Bubble Sort)
 */
void ordenarVetor(Item mochilaVetor[], int totalVetor) {
    if (totalVetor < 2) {
        printf("Nao e necessario ordenar (poucos itens).\n");
        return;
    }

    printf("Ordenando vetor por nome (Bubble Sort)... ");
    int trocou;
    for (int i = 0; i < totalVetor - 1; i++) {
        trocou = 0;
        for (int j = 0; j < totalVetor - i - 1; j++) {
            // Compara strings (nome)
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                // Troca
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
                trocou = 1;
            }
        }
        if (trocou == 0) break; // Otimização do Bubble Sort
    }
    printf("Concluido!\n");
    listarItensVetor(mochilaVetor, totalVetor);
}

/**
 * Nível 2: Busca Binária (apenas no vetor)
 */
void buscarBinariaVetor(Item mochilaVetor[], int totalVetor, int estaOrdenado) {
    if (!estaOrdenado) {
        printf("Erro: O vetor nao esta ordenado por nome.\n");
        printf("Use a opcao 'Ordenar Vetor' (5) antes de usar a busca binaria.\n");
        return;
    }
    if (totalVetor == 0) {
        printf("\nMochila (Vetor) vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n[Vetor] Nome do item (Busca Binaria): ");
    scanf("%29s", nomeBusca);
    limparBuffer();

    int comparacoes = 0; // Nível 2: Contador de operações
    int indice = -1;
    int inicio = 0;
    int fim = totalVetor - 1;

    while (inicio <= fim) {
        comparacoes++; // Conta a comparação principal do loop
        int meio = inicio + (fim - inicio) / 2;
        int cmp = strcmp(mochilaVetor[meio].nome, nomeBusca);

        if (cmp == 0) {
            indice = meio;
            break; // Encontrou
        } else if (cmp < 0) {
            inicio = meio + 1; // Item está na metade direita
        } else {
            fim = meio - 1; // Item está na metade esquerda
        }
    }

    if (indice != -1) {
        printf("Item encontrado!\n");
        printf("  Nome: %s (Tipo: %s, Qtd: %d)\n",
            mochilaVetor[indice].nome, mochilaVetor[indice].tipo, mochilaVetor[indice].quantidade);
    } else {
        printf("Item '%s' nao encontrado.\n", nomeBusca);
    }
    printf("Busca Binaria (Vetor) realizou %d comparacoes.\n", comparacoes);
}


// --- IMPLEMENTAÇÃO - MOCHILA (LISTA ENCADEADA) ---

void menuLista(No** lista) {
    int opcaoLista = -1;
    do {
        printf("\n--- Mochila (LISTA ENCADEADA) ---\n");
        printf("1. Inserir Item (no inicio)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar (Sequencial)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Opcao: ");
        scanf("%d", &opcaoLista);
        limparBuffer();

        switch (opcaoLista) {
            case 1:
                inserirItemLista(lista);
                break;
            case 2:
                removerItemLista(lista);
                break;
            case 3:
                listarItensLista(*lista);
                break;
            case 4:
                buscarSequencialLista(*lista);
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
        if(opcaoLista != 0 && opcaoLista != 3) pausar();

    } while (opcaoLista != 0);
}

/**
 * Nível 2: Inserir na Lista Encadeada (Inserção na cabeça)
 */
void inserirItemLista(No** lista) {
    // Aloca memória para o novo nó
    No* novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro: Falha ao alocar memoria (malloc)!\n");
        return;
    }

    // Coleta os dados do item
    printf("\n[Lista] Nome do item: ");
    scanf("%29s", novoNo->dados.nome);
    limparBuffer();
    printf("[Lista] Tipo do item: ");
    scanf("%19s", novoNo->dados.tipo);
    limparBuffer();
    printf("[Lista] Quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    limparBuffer();

    // "Engata" o novo nó no início da lista
    novoNo->proximo = *lista;
    *lista = novoNo; // A cabeça da lista agora é o novo nó

    printf("Item adicionado a lista encadeada.\n");
}

void listarItensLista(No* lista) {
    if (lista == NULL) {
        printf("\nMochila (Lista) esta vazia.\n");
        return;
    }

    printf("\n--- Itens na Lista ---\n");
    printf("| %-20s | %-15s | %s\n", "Nome", "Tipo", "Qtd.");
    printf("---------------------------------------------------\n");

    No* temp = lista;
    while (temp != NULL) {
        printf("| %-20s | %-15s | %d\n",
               temp->dados.nome, temp->dados.tipo, temp->dados.quantidade);
        temp = temp->proximo; // Avança para o próximo nó
    }
    printf("---------------------------------------------------\n");
}

/**
 * Nível 2: Remoção da Lista Encadeada
 */
void removerItemLista(No** lista) {
    if (*lista == NULL) {
        printf("\nMochila (Lista) vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n[Lista] Nome do item a remover: ");
    scanf("%29s", nomeBusca);
    limparBuffer();

    No* temp = *lista;
    No* anterior = NULL;

    // Procura o item
    while (temp != NULL && strcmp(temp->dados.nome, nomeBusca) != 0) {
        anterior = temp;
        temp = temp->proximo;
    }

    // Se temp é NULL, o item não foi encontrado
    if (temp == NULL) {
        printf("Item '%s' nao encontrado na lista.\n", nomeBusca);
        return;
    }

    // Se anterior é NULL, o item a ser removido é a cabeça da lista
    if (anterior == NULL) {
        *lista = temp->proximo; // A nova cabeça é o próximo
    } else {
        // Se for um item no meio ou fim
        anterior->proximo = temp->proximo;
    }

    free(temp); // Libera a memória do nó removido
    printf("Item '%s' removido da lista.\n", nomeBusca);
}

void buscarSequencialLista(No* lista) {
    if (lista == NULL) {
        printf("\nMochila (Lista) vazia.\n");
        return;
    }
    char nomeBusca[30];
    printf("\n[Lista] Nome do item (Busca Sequencial): ");
    scanf("%29s", nomeBusca);
    limparBuffer();

    int comparacoes = 0; // Nível 2: Contador de operações
    No* temp = lista;
    No* encontrado = NULL;

    while (temp != NULL) {
        comparacoes++; // Conta cada strcmp
        if (strcmp(temp->dados.nome, nomeBusca) == 0) {
            encontrado = temp;
            break;
        }
        temp = temp->proximo;
    }

    if (encontrado != NULL) {
        printf("Item encontrado!\n");
        printf("  Nome: %s (Tipo: %s, Qtd: %d)\n",
            encontrado->dados.nome, encontrado->dados.tipo, encontrado->dados.quantidade);
    } else {
        printf("Item '%s' nao encontrado.\n", nomeBusca);
    }
    printf("Busca Sequencial (Lista) realizou %d comparacoes.\n", comparacoes);
}

/**
 * Nível 2: Gerenciamento de Memória (free)
 * Percorre a lista e libera a memória de cada nó.
 */
void liberarLista(No** lista) {
    No* atual = *lista;
    No* proximo;

    while (atual != NULL) {
        proximo = atual->proximo; // Guarda a referência para o próximo
        free(atual);              // Libera o nó atual
        atual = proximo;          // Move para o próximo
    }
    *lista = NULL; // Garante que a lista está vazia
}
