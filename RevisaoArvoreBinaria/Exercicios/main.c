/*
1. Escreva uma função que calcule o número de nós de uma árvore binária.
2. Escreva uma função iterativa para calcular a altura de uma árvore binária.
3. Escreva um algoritmo (só uma função) que encontre o menor e o maior valor
armazenados em uma árvore binária de busca já construída.
4. Implementar uma função que retorne a quantidade de folhas de uma árvore
binária. Essa função deve obedecer ao protótipo: int folhas(Arvore *raiz)
5. Implementar uma função que compare se duas árvores binárias são iguais. Essa
função deve obedecer ao protótipo: int igual(Arvore *a, Arvore *b)
6. Escreva uma função que verifica se uma árvore de busca é válida.
int verifica_busca(No* t);
*/

#include <stdio.h>
#include <malloc.h>
#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct aux{
    TIPOCHAVE chave;
    struct aux *esq, *dir;
} NO;

typedef NO* PONT;

PONT criarNovoNo(TIPOCHAVE ch){
    PONT novoNo = (PONT) malloc(sizeof(NO));
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->chave = ch;
    return novoNo;
}

bool inserirAux(PONT raiz, TIPOCHAVE ch){
    if(raiz->chave > ch){
        if(raiz->esq == NULL){
            raiz->esq = criarNovoNo(ch);
            return true;
        }else return inserirAux(raiz->esq, ch);
    }else{
        if(raiz->dir == NULL){
            raiz->dir = criarNovoNo(ch);
            return true;
        }else return inserirAux(raiz->dir, ch);
    }
}

bool inserirNo(PONT * raiz, TIPOCHAVE novaChave){
    if(*raiz == NULL){
        *raiz = criarNovoNo(novaChave);
        return true;
    }
    else return inserirAux(*raiz, novaChave);
}

void exibirArvoreEmOrdem(PONT raiz){
    if(raiz == NULL){
        return;
    }
    exibirArvoreEmOrdem(raiz->esq);
    printf("| %d ", raiz->chave);
    exibirArvoreEmOrdem(raiz->dir);
}

void destruirAux(PONT subRaiz){
    if(subRaiz){
        destruirAux(subRaiz->esq);
        destruirAux(subRaiz->dir);
        free(subRaiz);
    }
}

void destruirArvore(PONT * raiz){
    destruirAux(*raiz);
    printf("Arvore destruida.\n\n");
    *raiz = NULL;
}

void inicializar(PONT * raiz){
    *raiz = NULL;
}

// EXERCÍCIO 1: Função para contar o número de folhas na árvore
int contarFolhas(PONT raiz){
    if(raiz == NULL){
        return 0;
    }
    if(raiz->esq == NULL && raiz->dir == NULL){
        return 1;
    }
    return contarFolhas(raiz->esq) + contarFolhas(raiz->dir);
}

int main(){
    PONT raiz;

    inicializar(&raiz);
    inserirNo(&raiz, 50);
    inserirNo(&raiz, 30);
    inserirNo(&raiz, 70);
    inserirNo(&raiz, 20);
    inserirNo(&raiz, 40);
    inserirNo(&raiz, 60);
    inserirNo(&raiz, 80);

    printf("\n\t> Arvore em ordem:\n");
    exibirArvoreEmOrdem(raiz);
    printf("\n");

    int numFolhas = contarFolhas(raiz);
    printf("\n\t> Numero de folhas na arvore: %d\n", numFolhas);
    printf("\n");

    destruirArvore(&raiz);
    return 0;
}

