# Desafios de Estrutura de Dados em C - Simulação de Jogo

Este repositório contém uma série de desafios de programação em C focados na implementação de estruturas de dados e algoritmos, utilizando uma temática de jogos de sobrevivência. Os desafios progridem em complexidade, começando com manipulação básica de vetores e culminando em análise de performance de algoritmos de ordenação.

## 🚀 Sobre os Desafios

O projeto é dividido em três níveis, cada um em sua própria pasta dentro de `/src`.

### Nível 1: Inventário Inicial (Array Básico)

**Local:** `src/nivel1_inventario_simples/`

Implementação de um sistema de "mochila" (inventário) com capacidade fixa (10 itens). Utiliza um vetor simples de `structs`.

* **Struct:** `Item` (nome, tipo, quantidade)
* **Operações:** Inserir, Remover, Listar e Busca Sequencial.

### Nível 2: Mochila (Vetor vs. Lista Encadeada)

**Local:** `src/nivel2_vetor_vs_lista/`

Uma evolução do Nível 1, este programa implementa o sistema de mochila de duas formas paralelas para comparação:

1.  **Versão Vetor (Array):**
    * Implementa `inserir`, `remover`, `listar`, `buscarSequencial`.
    * Adiciona ordenação (Bubble Sort) por nome.
    * Adiciona **Busca Binária** (habilitada somente após a ordenação).
2.  **Versão Lista Encadeada:**
    * Implementa `inserir` (na cabeça), `remover`, `listar`, `buscarSequencial`.
    * Usa alocação dinâmica (`malloc`/`free`).

O foco deste nível é **contar o número de comparações** realizadas nas buscas (Sequencial vs. Binária) para demonstrar empiricamente a diferença de eficiência.

### Nível 3: Torre de Fuga (Algoritmos de Ordenação)

**Local:** `src/nivel3_algoritmos_ordenacao/`

O desafio final foca na análise de performance de diferentes algoritmos de ordenação aplicados a um vetor de `structs` (Componentes da torre).

* **Struct:** `Componente` (nome, tipo, prioridade)
* **Algoritmos Implementados:**
    * **Bubble Sort** (para ordenar por `nome`)
    * **Insertion Sort** (para ordenar por `tipo`)
    * **Selection Sort** (para ordenar por `prioridade`)
* **Análise de Desempenho:** O programa mede e exibe:
    1.  O **número de comparações** que cada algoritmo de ordenação realizou.
    2.  O **tempo de execução** de cada ordenação (usando `clock()` da `time.h`).
* **Busca Otimizada:** Inclui a **Busca Binária** por nome, que só pode ser executada após a ordenação por nome (Bubble Sort).
