/*
 * DESAFIO NÍVEL 1: INVENTÁRIO INICIAL (MOCHILA)
 * LINGUAGEM: C
 *
 * DESCRIÇÃO: Simula um inventário de jogador (mochila) com
 * capacidade fixa (10 itens) usando um vetor de structs.
 * Implementa as operações básicas: Inserir, Remover, Listar e Buscar (Sequencial).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACIDADE_MOCHILA 10

// Nível 1: Criação da struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Protótipos das Funções
void limparBuffer();
void inserirItem(Item mochila[], int* totalItens);
void removerItem(Item mochila[], int* totalItens);
void listarItens(Item mochila[], int totalItens);
void buscarItem(Item mochila[], int totalItens);
int encontrarIndiceItem(Item mochila[], int totalItens, char* nome);

int main() {
    // Nível 1: Vetor de structs
    Item mochila[CAPACIDADE_MOCHILA];
    int totalItens = 0; // Controla quantos itens estão no vetor
    int opcao = -1;

    do {
        printf("\n--- MOCHILA (NIVEL 1) ---\n");
        printf("Itens na mochila: %d/%d\n", totalItens, CAPACIDADE_MOCHILA);
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer(); // Limpa o '\n' deixado pelo scanf

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItem(mochila, totalItens);
                break;
            case 0:
                printf("Saindo do sistema de inventario...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

        // Requisito: Listar itens após cada operação (exceto sair e listar)
        if (opcao == 1 || opcao == 2 || opcao == 4) {
             if (totalItens > 0) {
                printf("\n--- Estado Atual da Mochila ---\n");
                listarItens(mochila, totalItens);
             }
        }

    } while (opcao != 0);

    return 0;
}

/**
 * Limpa o buffer de entrada (stdin) para evitar problemas
 * com leituras mistas (scanf, fgets).
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Nível 1: Cadastro de itens
 * Adiciona um novo item ao vetor 'mochila' se houver espaço.
 */
void inserirItem(Item mochila[], int* totalItens) {
    if (*totalItens >= CAPACIDADE_MOCHILA) {
        printf("Erro: Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("\n--- Inserir Novo Item ---\n");
    Item novoItem;

    printf("Nome do item (ex: KitMedico): ");
    // Usamos scanf com limite (%29s) para evitar overflow do buffer char[30]
    scanf("%29s", novoItem.nome);
    limparBuffer();

    printf("Tipo do item (ex: Cura, Arma, Municao): ");
    scanf("%19s", novoItem.tipo);
    limparBuffer();

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBuffer();

    // Adiciona o item na próxima posição livre
    mochila[*totalItens] = novoItem;
    (*totalItens)++; // Incrementa o contador total de itens

    printf("Item '%s' adicionado com sucesso!\n", novoItem.nome);
}

/**
 * Nível 1: Listagem dos itens
 * Exibe todos os itens atualmente na mochila.
 */
void listarItens(Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("\nMochila esta vazia.\n");
        return;
    }

    printf("\n--- Itens na Mochila (%d) ---\n", totalItens);
    printf("---------------------------------------------------\n");
    printf("| %-20s | %-15s | %s\n", "Nome", "Tipo", "Qtd.");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < totalItens; i++) {
        printf("| %-20s | %-15s | %d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
    printf("---------------------------------------------------\n");
}

/**
 * Nível 1: Busca sequencial
 * Encontra um item pelo nome e exibe seus dados.
 */
void buscarItem(Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("\nMochila esta vazia. Nao ha o que buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item a buscar: ");
    scanf("%29s", nomeBusca);
    limparBuffer();

    int indice = encontrarIndiceItem(mochila, totalItens, nomeBusca);

    if (indice != -1) {
        printf("Item encontrado!\n");
        printf("  Nome: %s\n", mochila[indice].nome);
        printf("  Tipo: %s\n", mochila[indice].tipo);
        printf("  Qtd.: %d\n", mochila[indice].quantidade);
    } else {
        printf("Item '%s' nao encontrado na mochila.\n", nomeBusca);
    }
}

/**
 * Nível 1: Remoção de itens
 * Encontra um item pelo nome e o remove, "puxando" os
 * itens subsequentes para preencher o espaço.
 */
void removerItem(Item mochila[], int* totalItens) {
     if (*totalItens == 0) {
        printf("\nMochila esta vazia. Nao ha o que remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item a remover: ");
    scanf("%29s", nomeBusca);
    limparBuffer();

    int indice = encontrarIndiceItem(mochila, *totalItens, nomeBusca);

    if (indice == -1) {
        printf("Item '%s' nao encontrado para remocao.\n", nomeBusca);
        return;
    }

    // "Desloca" todos os itens à direita do item removido para a esquerda
    for (int i = indice; i < (*totalItens - 1); i++) {
        mochila[i] = mochila[i + 1];
    }

    (*totalItens)--; // Decrementa o número total de itens
    printf("Item '%s' removido com sucesso!\n", nomeBusca);
}

/**
 * Função auxiliar para busca sequencial.
 * Retorna o índice do item se encontrado, ou -1 se não.
 */
int encontrarIndiceItem(Item mochila[], int totalItens, char* nome) {
    for (int i = 0; i < totalItens; i++) {
        // Compara o nome do item na mochila com o nome buscado
        if (strcmp(mochila[i].nome, nome) == 0) {
            return i; // Retorna o índice onde o item foi encontrado
        }
    }
    return -1; // Item não encontrado
}
