/*
 * DESAFIO NÍVEL 3: TORRE DE FUGA (ALGORITMOS DE ORDENAÇÃO)
 * LINGUAGEM: C
 *
 * DESCRIÇÃO: Simula a organização de componentes para uma torre de fuga.
 * Implementa 3 algoritmos de ordenação e 1 de busca, medindo o
 * desempenho (comparações e tempo) de cada um.
 *
 * 1. Bubble Sort (por Nome)
 * 2. Insertion Sort (por Tipo)
 * 3. Selection Sort (por Prioridade)
 * 4. Busca Binária (por Nome, após ordenação por nome)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Para clock()

#define MAX_COMPONENTES 20

// Nível 3: Criação da struct Componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // 1 a 10
} Componente;

// Protótipos
void limparBuffer();
void pausar();
void cadastrarComponente(Componente torre[], int* total);
void mostrarComponentes(Componente torre[], int total);

// Funções de Ordenação (com contagem de comparações)
void bubbleSortNome(Componente torre[], int total, long* comparacoes);
void insertionSortTipo(Componente torre[], int total, long* comparacoes);
void selectionSortPrioridade(Componente torre[], int total, long* comparacoes);

// Função de Busca
int buscaBinariaPorNome(Componente torre[], int total, char* nomeBusca, long* comparacoes);

int main() {
    Componente torre[MAX_COMPONENTES];
    int totalComponentes = 0;
    // Flag para garantir que a busca binária só rode no vetor ordenado por nome
    int estaOrdenadoPorNome = 0;

    int opcao = -1;
    long comparacoes = 0; // Nível 3: Medição de desempenho
    clock_t inicio, fim;  // Nível 3: Medição de tempo
    double tempoGasto;

    // Copia de segurança para restaurar a ordem original
    Componente torreBackup[MAX_COMPONENTES];
    int totalBackup = 0;


    do {
        printf("\n--- NIVEL 3: TORRE DE FUGA (ORDENACAO) ---\n");
        printf("Componentes catalogados: %d/%d\n", totalComponentes, MAX_COMPONENTES);
        printf("Estado: %s\n", estaOrdenadoPorNome ? "Ordenado por Nome" : "Nao ordenado");
        printf("--------------------------------------------\n");
        printf("1. Cadastrar Componente\n");
        printf("2. Listar Componentes (Estado Atual)\n");
        printf("3. [ORDENAR] por Nome (Bubble Sort)\n");
        printf("4. [ORDENAR] por Tipo (Insertion Sort)\n");
        printf("5. [ORDENAR] por Prioridade (Selection Sort)\n");
        printf("6. [BUSCAR] Componente-Chave (Busca Binaria por Nome)\n");
        printf("7. Restaurar ordem original (Backup)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarComponente(torre, &totalComponentes);
                // Atualiza o backup
                totalBackup = totalComponentes;
                memcpy(torreBackup, torre, sizeof(torre));
                estaOrdenadoPorNome = 0;
                break;
            case 2:
                mostrarComponentes(torre, totalComponentes);
                break;
            case 3: // Bubble Sort por Nome
                printf("Iniciando Bubble Sort (por Nome)...\n");
                comparacoes = 0;
                inicio = clock();
                bubbleSortNome(torre, totalComponentes, &comparacoes);
                fim = clock();
                tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

                printf("Bubble Sort concluido!\n");
                printf("Tempo: %.6f segundos | Comparacoes: %ld\n", tempoGasto, comparacoes);
                estaOrdenadoPorNome = 1;
                mostrarComponentes(torre, totalComponentes);
                break;
            case 4: // Insertion Sort por Tipo
                printf("Iniciando Insertion Sort (por Tipo)...\n");
                comparacoes = 0;
                inicio = clock();
                insertionSortTipo(torre, totalComponentes, &comparacoes);
                fim = clock();
                tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

                printf("Insertion Sort concluido!\n");
                printf("Tempo: %.6f segundos | Comparacoes: %ld\n", tempoGasto, comparacoes);
                estaOrdenadoPorNome = 0; // Ordenação por tipo "quebra" a por nome
                mostrarComponentes(torre, totalComponentes);
                break;
            case 5: // Selection Sort por Prioridade
                printf("Iniciando Selection Sort (por Prioridade)...\n");
                comparacoes = 0;
                inicio = clock();
                selectionSortPrioridade(torre, totalComponentes, &comparacoes);
                fim = clock();
                tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

                printf("Selection Sort concluido!\n");
                printf("Tempo: %.6f segundos | Comparacoes: %ld\n", tempoGasto, comparacoes);
                estaOrdenadoPorNome = 0; // Ordenação por prioridade "quebra" a por nome
                mostrarComponentes(torre, totalComponentes);
                break;
            case 6: // Busca Binária por Nome
                if (!estaOrdenadoPorNome) {
                    printf("Erro: Vetor nao esta ordenado por nome.\n");
                    printf("Execute a opcao 3 (Ordenar por Nome) antes de buscar.\n");
                } else {
                    char nomeBusca[30];
                    printf("\nDigite o nome do Componente-Chave a buscar: ");
                    scanf("%29s", nomeBusca);
                    limparBuffer();

                    comparacoes = 0;
                    int indice = buscaBinariaPorNome(torre, totalComponentes, nomeBusca, &comparacoes);

                    if (indice != -1) {
                        printf("Componente-Chave '%s' ENCONTRADO!\n", nomeBusca);
                        printf("  Tipo: %s, Prioridade: %d\n", torre[indice].tipo, torre[indice].prioridade);
                    } else {
                        printf("Componente-Chave '%s' NAO ENCONTRADO!\n", nomeBusca);
                    }
                    printf("Busca Binaria realizou %ld comparacoes.\n", comparacoes);
                }
                break;
            case 7:
                 printf("Restaurando componentes para a ordem original de cadastro...\n");
                 totalComponentes = totalBackup;
                 memcpy(torre, torreBackup, sizeof(torreBackup));
                 estaOrdenadoPorNome = 0;
                 mostrarComponentes(torre, totalComponentes);
                 break;
            case 0:
                printf("Saindo do sistema da torre...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
        if (opcao != 0) pausar();

    } while (opcao != 0);

    return 0;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar() {
    printf("\nPressione Enter para continuar...");
    limparBuffer();
}

void cadastrarComponente(Componente torre[], int* total) {
    if (*total >= MAX_COMPONENTES) {
        printf("Erro: Limite de componentes atingido (%d).\n", MAX_COMPONENTES);
        return;
    }

    printf("\n--- Cadastrar Novo Componente ---\n");
    printf("Nome (ex: ChipCentral): ");
    scanf("%29s", torre[*total].nome);
    limparBuffer();
    printf("Tipo (ex: Controle, Suporte, Propulsao): ");
    scanf("%19s", torre[*total].tipo);
    limparBuffer();
    printf("Prioridade (1-10): ");
    scanf("%d", &torre[*total].prioridade);
    limparBuffer();

    (*total)++;
    printf("Componente cadastrado com sucesso!\n");
}

void mostrarComponentes(Componente torre[], int total) {
    if (total == 0) {
        printf("\nNenhum componente cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Componentes (%d) ---\n", total);
    printf("-----------------------------------------------------------\n");
    printf("| %-20s | %-15s | %s\n", "Nome", "Tipo", "Prioridade");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("| %-20s | %-15s | %d\n",
               torre[i].nome,
               torre[i].tipo,
               torre[i].prioridade);
    }
    printf("-----------------------------------------------------------\n");
}

/**
 * Nível 3: Bubble sort (por nome)
 */
void bubbleSortNome(Componente torre[], int total, long* comparacoes) {
    int trocou;
    for (int i = 0; i < total - 1; i++) {
        trocou = 0;
        for (int j = 0; j < total - i - 1; j++) {
            (*comparacoes)++; // Conta a comparação
            if (strcmp(torre[j].nome, torre[j + 1].nome) > 0) {
                // Troca
                Componente temp = torre[j];
                torre[j] = torre[j + 1];
                torre[j + 1] = temp;
                trocou = 1;
            }
        }
        if (trocou == 0) break;
    }
}

/**
 * Nível 3: Insertion sort (por tipo)
 */
void insertionSortTipo(Componente torre[], int total, long* comparacoes) {
    int i, j;
    Componente chave;
    for (i = 1; i < total; i++) {
        chave = torre[i];
        j = i - 1;

        // Move elementos que são maiores que a chave (baseado no tipo)
        while (j >= 0) {
            (*comparacoes)++; // Conta a comparação
            if (strcmp(torre[j].tipo, chave.tipo) > 0) {
                torre[j + 1] = torre[j];
                j = j - 1;
            } else {
                break; // Para o while interno se a condição não for atendida
            }
        }
        torre[j + 1] = chave;
    }
}

/**
 * Nível 3: Selection sort (por prioridade)
 */
void selectionSortPrioridade(Componente torre[], int total, long* comparacoes) {
    int i, j, min_idx;

    for (i = 0; i < total - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < total; j++) {
            (*comparacoes)++; // Conta a comparação
            // Compara por prioridade (int)
            if (torre[j].prioridade < torre[min_idx].prioridade) {
                min_idx = j;
            }
        }
        // Troca o menor encontrado com o primeiro elemento
        if(min_idx != i) {
            Componente temp = torre[min_idx];
            torre[min_idx] = torre[i];
            torre[i] = temp;
        }
    }
}

/**
 * Nível 3: Busca binária (por nome)
 */
int buscaBinariaPorNome(Componente torre[], int total, char* nomeBusca, long* comparacoes) {
    int inicio = 0;
    int fim = total - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        (*comparacoes)++; // Conta a comparação
        int cmp = strcmp(torre[meio].nome, nomeBusca);

        if (cmp == 0) {
            return meio; // Encontrou
        }
        if (cmp < 0) {
            inicio = meio + 1; // Busca na metade direita
        } else {
            fim = meio - 1; // Busca na metade esquerda
        }
    }
    return -1; // Não encontrou
}
