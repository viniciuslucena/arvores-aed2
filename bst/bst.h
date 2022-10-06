#ifndef BST_H
#define BST_H

typedef struct no
{
    int valor;
    struct no *esq, *dir;
} no;

typedef no *arvore;

arvore inserir(arvore raiz, int valor);
int altura(arvore raiz);
arvore remover(arvore raiz, int valor);

#endif
