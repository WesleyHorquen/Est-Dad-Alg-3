#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *esq, *dir;
    short altura; //utilizar menos memória que int
} NO;

/* 
Função que cria um novo nó
x -> valor a ser inserido no nó
Retorna: o endereço do novo nó criado
*/
NO* novoNo(int x){
    NO *novo = malloc(sizeof(NO));
    if(novo){
        novo->valor = x;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 0;
    }else{
        printf("\n> Erro ao alocar memória para o novo nó.\n");
    }
    return novo;
}

/*
Retorna o maior dentre dois valores
a, b -> altura de dois nós da árvore
Retorna: o maior valor entre a e b
*/
short maior(short a, short b){
    return (a > b) ? a : b;
}

/*
Retorna a altura de um nó
ou 0 caso ele seja null
*/
short alturaDoNo(NO *no){
    if(no == NULL){
        return 0;
    }else{
        return no->altura;
    }
}

// Calcula e retorna o fator de balanceamento de um nó
short fatorDeBalanceamento(NO *no){
    if(no){
        return alturaDoNo(no->dir) - alturaDoNo(no->esq);
    }else{
        return 0; // Nó nulo tem fator de balanceamento 0
    }
}

//Função para a rotação à esquerda
NO* rotacaoEsquerda(NO *A){
    NO *B, *f;

    //A é o ancestral do nó B, e f é o filho esquerdo de B
    B = A->dir;
    f = B->esq;

    B->esq = A;
    A->dir = f;

    A->altura = maior(alturaDoNo(A->esq), alturaDoNo(A->dir)) + 1;
    B->altura = maior(alturaDoNo(B->esq), alturaDoNo(B->dir)) + 1;
    return B;
}

//Função para a rotação à direita
NO* rotacaoDireita(NO *A){
    NO *B, *f;

    //A é o ancestral do nó B, e f é o filho direito de B
    B = A->esq;
    f = B->dir;

    B->dir = A;
    A->esq = f;

    A->altura = maior(alturaDoNo(A->esq), alturaDoNo(A->dir)) + 1;
    B->altura = maior(alturaDoNo(B->esq), alturaDoNo(B->dir)) + 1;
    return B;
}

//Função para a rotação dupla à esquerda
NO* rotacaoDireitaEsquerda(NO *A){
    A->dir = rotacaoDireita(A->dir);
    return rotacaoEsquerda(A);
}

//Função para a rotação dupla à direita
NO* rotacaoEsquerdaDireita(NO *A){
    A->esq = rotacaoEsquerda(A->esq);
    return rotacaoDireita(A);
}

//Liberar memória da árvore
void liberaArvore(NO *raiz){
    if(raiz != NULL){
        liberaArvore(raiz->esq);
        liberaArvore(raiz->dir);
        free(raiz);
    }
}

int main(){
    // Exemplo de uso das funções de rotação
    NO *raiz = novoNo(10);
    raiz->dir = novoNo(20);
    raiz->dir->dir = novoNo(30);

    printf("\n> Fator de balanceamento antes da rotação: %d\n", fatorDeBalanceamento(raiz));
    
    raiz = rotacaoEsquerda(raiz);
    
    printf("\n> Fator de balanceamento após a rotação: %d\n", fatorDeBalanceamento(raiz));
    
    // Exemplo de rotação dupla
    raiz->esq = novoNo(5);
    raiz->esq->dir = novoNo(7);
    printf("\n> Fator de balanceamento antes da rotação dupla: %d\n", fatorDeBalanceamento(raiz));
    raiz = rotacaoEsquerdaDireita(raiz);
    printf("\n> Fator de balanceamento após a rotação dupla: %d\n", fatorDeBalanceamento(raiz));
    
    // Liberar memória da árvore
    liberaArvore(raiz);
    return 0;
}