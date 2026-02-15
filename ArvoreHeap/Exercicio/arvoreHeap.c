#include <stdio.h>
#include <windows.h>  // Para SetConsoleOutputCP
#include <limits.h> // Para INT_MIN

/*
 * Função: verifica_heap
 * Parâmetros:
 *   - heap: vetor de inteiros (índice 0 é o primeiro elemento)
 *   - n: número de elementos no vetor
 * Retorno:
 *   - 1 se for um max-heap
 *   - 0 se NÃO for um max-heap
 * 
 * O que é um max-heap?
 * Para todo nó i:
 *   heap[i] >= heap[filho_esquerdo(i)]
 *   heap[i] >= heap[filho_direito(i)]
 * 
 * Em vetor:
 *   - Filho esquerdo do índice i: 2*i + 1
 *   - Filho direito do índice i: 2*i + 2
 *   - Pai do índice i: (i-1)/2
 */
int verifica_heap(int *heap, int n) {
    // Percorre todos os nós que têm filhos
    // Último nó que tem filhos está em posição (n/2 - 1)
    for (int i = 0; i <= n/2 - 1; i++) {
        int esquerdo = 2*i + 1;
        int direito = 2*i + 2;
        
        // Verifica filho esquerdo
        if (esquerdo < n) {  // Se existir filho esquerdo
            if (heap[i] < heap[esquerdo]) {
                return 0;  // Violou a propriedade do max-heap
            }
        }
        
        // Verifica filho direito
        if (direito < n) {  // Se existir filho direito
            if (heap[i] < heap[direito]) {
                return 0;  // Violou a propriedade do max-heap
            }
        }
    }
    
    return 1;  // É um max-heap
}

// Exemplo de uso
void teste_exercicio1() {
    printf("\t=== Exercício 1: Verificação de Max-Heap ===\n\n");
    
    // Exemplo 1: É um max-heap
    int heap1[] = {90, 15, 10, 7, 12, 2, 7};
    int n1 = 7;
    printf("Vetor 1: ");
    for (int i = 0; i < n1; i++) printf("%d ", heap1[i]);
    printf("\nÉ max-heap? %s\n\n", verifica_heap(heap1, n1) ? "SIM" : "NÃO");
    
    // Exemplo 2: NÃO é um max-heap (15 < 20)
    int heap2[] = {90, 15, 10, 7, 20, 2, 7};
    int n2 = 7;
    printf("Vetor 2: ");
    for (int i = 0; i < n2; i++) printf("%d ", heap2[i]);
    printf("\nÉ max-heap? %s\n\n", verifica_heap(heap2, n2) ? "SIM" : "NÃO");
    
    // Exemplo 3: É um max-heap (apenas 1 elemento)
    int heap3[] = {10};
    int n3 = 1;
    printf("Vetor 3: ");
    for (int i = 0; i < n3; i++) printf("%d ", heap3[i]);
    printf("\nÉ max-heap? %s\n", verifica_heap(heap3, n3) ? "SIM" : "NÃO");
}
/*
 * Função: chave_minima
 * Parâmetros:
 *   - heap: vetor que representa um max-heap
 *   - n: número de elementos
 * Retorno: menor valor encontrado no heap
 * 
 * OBSERVAÇÃO IMPORTANTE:
 * Em um max-heap, o menor elemento NÃO está necessariamente na raiz.
 * Ele está entre os nós folha (último nível da árvore).
 * 
 * Por que?
 * - A raiz é o MAIOR elemento
 * - A propriedade do max-heap só garante que pais são >= filhos
 * - Não há garantia sobre a ordem entre irmãos ou folhas
 * 
 * Onde procurar?
 * Nos elementos das folhas, que são os últimos n/2 elementos do vetor.
 */
int chave_minima(int* heap, int n) {
    if (n <= 0) {
        printf("Heap vazio!\n");
        return INT_MIN;
    }
    
    // A menor chave está entre as folhas
    // As folhas começam na posição floor(n/2)
    int inicio_folhas = n / 2;
    int menor = heap[inicio_folhas]; // Começa com a primeira folha
    
    // Percorre todas as folhas para encontrar o menor
    for (int i = inicio_folhas + 1; i < n; i++) {
        if (heap[i] < menor) {
            menor = heap[i];
        }
    }
    
    return menor;
}

// Explicação visual:
// Heap: [90, 15, 10, 7, 12, 2, 7, 3, 5]
// Índices: 0:90, 1:15, 2:10, 3:7, 4:12, 5:2, 6:7, 7:3, 8:5
// n = 9, n/2 = 4 (floor de 9/2)
// Folhas: índices 4, 5, 6, 7, 8 -> valores: 12, 2, 7, 3, 5
// Menor: 2 (índice 5)

void teste_exercicio2() {
    printf("\n\t=== Exercício 2: Chave Mínima em Max-Heap ===\n\n");
    
    int heap[] = {90, 15, 10, 7, 12, 2, 7, 3, 5};
    int n = 9;
    
    printf("Max-Heap: ");
    for (int i = 0; i < n; i++) printf("%d ", heap[i]);
    printf("\n");
    
    printf("Raiz (máximo): %d\n", heap[0]);
    printf("Menor elemento: %d\n", chave_minima(heap, n));
    printf("\nPor que buscar apenas nas folhas?\n");
    printf("- Folhas: índices %d a %d\n", n/2, n-1);
    printf("- Folhas: valores ");
    for (int i = n/2; i < n; i++) printf("%d ", heap[i]);
    printf("\n");
}
void exercicio3_explicacao() {
    printf("\n\t=== Exercício 3: Posições das Chaves ===\n\n");
    
    printf("HEAP DE MÁXIMO: [100, 36, 25, 19, 17, 7, 2, 3, 1, 2, 7]\n");
    printf("Índices:        0   1   2   3   4  5  6  7  8  9  10\n\n");
    
    printf("Análise:\n");
    printf("1. MAIOR chave: SEMPRE na posição 0 (raiz)\n");
    printf("   Exemplo: 100 está no índice 0\n\n");
    
    printf("2. SEGUNDA MAIOR chave:\n");
    printf("   - Está entre os filhos da raiz (índices 1 e 2)\n");
    printf("   - No exemplo: 36 (índice 1) ou 25 (índice 2)\n");
    printf("   - É o MAIOR dos filhos da raiz\n");
    printf("   - Sempre no NÍVEL 1 da árvore\n\n");
    
    printf("3. TERCEIRA MAIOR chave:\n");
    printf("   - Pode estar em:\n");
    printf("     a) O outro filho da raiz (se não for a segunda maior)\n");
    printf("     b) Filhos do filho maior (nível 2)\n");
    printf("   - No exemplo: 25 (índice 2) ou 19 (índice 3) ou 17 (índice 4)\n");
    printf("   - É o MAIOR entre os não escolhidos anteriormente\n\n");
    
    printf("4. SEGUNDA MENOR chave:\n");
    printf("   - Está entre as FOLHAS (último nível)\n");
    printf("   - Folhas: índices floor(n/2) até n-1\n");
    printf("   - No exemplo (n=11): folhas são índices 5 a 10\n");
    printf("   - Folhas: 7, 2, 3, 1, 2, 7\n");
    printf("   - Segunda menor: 2 (depois do 1)\n");
    printf("   - Pode ter DUAS ocorrências do mesmo valor\n\n");
    
    printf("5. TERCEIRA MENOR chave:\n");
    printf("   - Também está entre as folhas\n");
    printf("   - É a terceira menor entre todos os valores das folhas\n");
    printf("   - No exemplo: 2, 3 ou 7 (depende da ordem)\n\n");
    
    printf("RESUMO DAS POSIÇÕES:\n");
    printf("Maior:           posição 0 (raiz)\n");
    printf("Segunda maior:   nível 1 (índices 1 ou 2)\n");
    printf("Terceira maior:  nível 1 ou 2\n");
    printf("Segunda menor:   entre as folhas\n");
    printf("Terceira menor:  entre as folhas\n");
}

// Função auxiliar para visualizar a árvore
void visualizar_heap_com_indices(int *heap, int n) {
    printf("\nVisualização da árvore:\n");
    printf("          %d[0]\n", heap[0]);
    printf("         /    \\\n");
    if (n > 1) printf("    %d[1]    %d[2]\n", heap[1], heap[2]);
    if (n > 3) printf("   /  \\     /  \\\n");
    if (n > 3) printf("%d[3] %d[4] ", heap[3], heap[4]);
    if (n > 5) printf("%d[5] %d[6]\n", heap[5], heap[6]);
    printf("\nÍndices entre colchetes []\n");
}
void exercicio4_explicacao() {
    printf("\n\t=== Exercício 4: Quantidade de Elementos por Profundidade ===\n\n");
    
    printf("PROFUNDIDADE d: número de níveis da raiz até as folhas mais distantes\n");
    printf("Profundidade 0: apenas raiz\n");
    printf("Profundidade 1: raiz + nível 1\n");
    printf("\n");
    
    printf("Para profundidade d:\n");
    printf("1. Número MÍNIMO de elementos:\n");
    printf("   - Árvore completa exceto o último nível\n");
    printf("   - Último nível tem APENAS 1 nó\n");
    printf("   - Fórmula: (2^d - 1) + 1 = 2^d\n");
    printf("   - Exemplo d=2: 2² = 4 elementos\n");
    printf("   - Visual: nível 0:1, nível 1:2, nível 2:1 (total 4)\n\n");
    
    printf("2. Número MÁXIMO de elementos:\n");
    printf("   - Árvore COMPLETAMENTE cheia\n");
    printf("   - Todos os níveis completos\n");
    printf("   - Fórmula: 2^(d+1) - 1\n");
    printf("   - Exemplo d=2: 2³ - 1 = 7 elementos\n");
    printf("   - Visual: nível 0:1, nível 1:2, nível 2:4 (total 7)\n\n");
    
    printf("TABELA RESUMO:\n");
    printf("+-----------+-----------+-----------+\n");
    printf("| Profund d |  MÍNIMO   |  MÁXIMO   |\n");
    printf("+-----------+-----------+-----------+\n");
    printf("|    0      |     1     |     1     |\n");
    printf("|    1      |     2     |     3     |\n");
    printf("|    2      |     4     |     7     |\n");
    printf("|    3      |     8     |    15     |\n");
    printf("|    4      |    16     |    31     |\n");
    printf("|    d      |   2^d     | 2^(d+1)-1 |\n");
    printf("+-----------+-----------+-----------+\n\n");
    
    printf("DEMONSTRAÇÃO:\n");
    printf("Profundidade 2 (d=2):\n");
    printf("Mínimo (4 elementos):\n");
    printf("     10\n");
    printf("    /  \\\n");
    printf("   20   30\n");
    printf("  /\n");
    printf(" 40\n");
    printf("\nMáximo (7 elementos):\n");
    printf("     10\n");
    printf("    /  \\\n");
    printf("   20   30\n");
    printf("  / \\   / \\\n");
    printf(" 40 50 60 70\n");
}

// Função para calcular programaticamente
void calcular_min_max(int d) {
    int minimo = 1 << d;  // 2^d (deslocamento de bits)
    int maximo = (1 << (d + 1)) - 1;  // 2^(d+1) - 1
    
    printf("Para profundidade %d:\n", d);
    printf("  Mínimo: %d elementos\n", minimo);
    printf("  Máximo: %d elementos\n", maximo);
}
int main() {
    // Muda a codificação do console para UTF-8
    SetConsoleOutputCP(65001);

    printf("=== LISTA DE EXERCÍCIOS: ÁRVORE BINÁRIA HEAP ===\n");
    
    // Teste Exercício 1
    teste_exercicio1();
    
    // Teste Exercício 2
    teste_exercicio2();
    
    // Explicação Exercício 3
    int exemplo_heap[] = {100, 36, 25, 19, 17, 7, 2, 3, 1, 2, 7};
    visualizar_heap_com_indices(exemplo_heap, 11);
    exercicio3_explicacao();
    
    // Explicação Exercício 4
    exercicio4_explicacao();
    
    // Cálculo para diferentes profundidades
    printf("\n=== CÁLCULOS PARA DIFERENTES PROFUNDIDADES ===\n");
    for (int d = 0; d <= 4; d++) {
        calcular_min_max(d);
    }
    
    return 0;
}