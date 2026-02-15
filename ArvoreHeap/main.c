#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_MAX 100

// ===== ESTRUTURA BÁSICA =====
// Um heap é apenas um array com regras de organização
typedef struct {
    int dados[TAMANHO_MAX];  // Array que guarda os elementos
    int tamanho;             // Quantos elementos tem no heap
} Heap;

// ===== FUNÇÕES AUXILIARES (matemática do heap) =====
int pai(int i) { return (i - 1) / 2; }           // Índice do pai
int esquerda(int i) { return 2 * i + 1; }        // Índice do filho esquerdo
int direita(int i) { return 2 * i + 2; }         // Índice do filho direito

// ===== MIN HEAP (pai menor que filhos) =====
void subirNoMinHeap(Heap *h, int i) {
    // Se chegou na raiz, para
    if (i == 0) return;
    
    int p = pai(i);
    
    // Se filho é MENOR que o pai (violou regra do MinHeap)
    if (h->dados[i] < h->dados[p]) {
        // Troca filho com pai
        int temp = h->dados[i];
        h->dados[i] = h->dados[p];
        h->dados[p] = temp;
        
        // Continua subindo
        subirNoMinHeap(h, p);
    }
}

void inserirNoMinHeap(Heap *h, int valor) {
    // Coloca o novo valor no final do array
    h->dados[h->tamanho] = valor;
    h->tamanho++;
    
    printf("Inseriu %d no MinHeap\n", valor);
    
    // Ajusta subindo o elemento
    subirNoMinHeap(h, h->tamanho - 1);
}

// ===== MAX HEAP (pai maior que filhos) =====
void subirNoMaxHeap(Heap *h, int i) {
    if (i == 0) return;
    
    int p = pai(i);
    
    // Se filho é MAIOR que o pai (violou regra do MaxHeap)
    if (h->dados[i] > h->dados[p]) {
        int temp = h->dados[i];
        h->dados[i] = h->dados[p];
        h->dados[p] = temp;
        
        subirNoMaxHeap(h, p);
    }
}

void inserirNoMaxHeap(Heap *h, int valor) {
    h->dados[h->tamanho] = valor;
    h->tamanho++;
    
    printf("Inseriu %d no MaxHeap\n", valor);
    
    subirNoMaxHeap(h, h->tamanho - 1);
}

// ===== DESCER ELEMENTO (para remoção) =====
void descerNoMinHeap(Heap *h, int i) {
    int menor = i;
    int e = esquerda(i);
    int d = direita(i);
    
    // Descobre qual é o menor entre pai, filho esq e filho dir
    if (e < h->tamanho && h->dados[e] < h->dados[menor])
        menor = e;
    if (d < h->tamanho && h->dados[d] < h->dados[menor])
        menor = d;
    
    // Se o menor não é o pai, troca e continua descendo
    if (menor != i) {
        int temp = h->dados[i];
        h->dados[i] = h->dados[menor];
        h->dados[menor] = temp;
        
        descerNoMinHeap(h, menor);
    }
}

int removerRaizMinHeap(Heap *h) {
    if (h->tamanho == 0) {
        printf("Heap vazio!\n");
        return -1;
    }
    
    int raiz = h->dados[0];  // Salva a raiz (menor elemento)
    
    // Coloca o último elemento na raiz
    h->dados[0] = h->dados[h->tamanho - 1];
    h->tamanho--;
    
    // Ajusta descendo a nova raiz
    descerNoMinHeap(h, 0);
    
    return raiz;
}

// ===== IMPRIMIR =====
void imprimirHeap(Heap *h, char *nome) {
    printf("%s: [", nome);
    for (int i = 0; i < h->tamanho; i++) {
        printf("%d", h->dados[i]);
        if (i < h->tamanho - 1) printf(", ");
    }
    printf("]\n");
}

void imprimirComoArvore(Heap *h) {
    printf("\nComo arvore:\n");
    int nivel = 0;
    int elementosNivel = 1;
    int cont = 0;
    
    for (int i = 0; i < h->tamanho; i++) {
        printf("%d ", h->dados[i]);
        cont++;
        
        if (cont == elementosNivel) {
            printf("\n");
            nivel++;
            elementosNivel *= 2;
            cont = 0;
        }
    }
    if (cont > 0) printf("\n");
}

// ===== MAIN =====
int main() {
    printf("\n=== ENTENDENDO HEAPS ===\n\n");
    
    // ===== MIN HEAP =====
    printf("--- MIN HEAP (pai MENOR que filhos) ---\n");
    Heap minHeap = {.tamanho = 0};
    
    inserirNoMinHeap(&minHeap, 8);
    inserirNoMinHeap(&minHeap, 5);
    inserirNoMinHeap(&minHeap, 3);
    inserirNoMinHeap(&minHeap, 10);
    inserirNoMinHeap(&minHeap, 1);
    
    imprimirHeap(&minHeap, "MinHeap");
    imprimirComoArvore(&minHeap);
    
    printf("\nRaiz (menor elemento): %d\n", minHeap.dados[0]);
    
    int removido = removerRaizMinHeap(&minHeap);
    printf("Removeu a raiz %d\n", removido);
    imprimirHeap(&minHeap, "MinHeap apos remocao");
    
    printf("\n");
    
    // ===== MAX HEAP =====
    printf("--- MAX HEAP (pai MAIOR que filhos) ---\n");
    Heap maxHeap = {.tamanho = 0};
    
    inserirNoMaxHeap(&maxHeap, 3);
    inserirNoMaxHeap(&maxHeap, 5);
    inserirNoMaxHeap(&maxHeap, 8);
    inserirNoMaxHeap(&maxHeap, 1);
    inserirNoMaxHeap(&maxHeap, 10);
    
    imprimirHeap(&maxHeap, "MaxHeap");
    imprimirComoArvore(&maxHeap);
    
    printf("\nRaiz (maior elemento): %d\n", maxHeap.dados[0]);
    
    return 0;
}