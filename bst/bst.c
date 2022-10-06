#include "bst.h"
#include <stdlib.h>
#include <stdio.h>

arvore inserir(arvore raiz, int valor)
{
    if (raiz == NULL)
    {
        no *novo = (no *)malloc(sizeof(no));

        novo->esq = NULL;
        novo->dir = NULL;
        novo->valor = valor;

        return novo;
    }
    else
    {
        if (valor > raiz->valor)
        {
            raiz->dir = inserir(raiz->dir, valor);
        }
        else
        {
            raiz->esq = inserir(raiz->esq, valor);
        }
        return raiz;
    }
}

arvore remover(arvore raiz, int valor)
{
    if (raiz == NULL)
        return NULL;

    if (raiz->valor == valor)
    {
        if (raiz->esq == NULL && raiz->dir == NULL)
        {
            free(raiz);
            return NULL;
        }
        if (raiz->esq == NULL && raiz->dir != NULL)
        {
            arvore retorno = raiz->dir;
            free(raiz);
            return retorno;
        }

        if (raiz->esq != NULL && raiz->dir == NULL)
        {
            arvore retorno = raiz->esq;
            free(raiz);
            return retorno;
        }

        if (raiz->esq != NULL && raiz->dir != NULL)
        {
            arvore retorno = raiz->esq;
            while (retorno->dir != NULL)
            {
                retorno = retorno->dir;
            }
            raiz->valor = retorno->valor;
            retorno->valor = valor;
            raiz->esq = remover(raiz->esq, valor);
            return raiz;
        }
    }
    else
    {
        if (valor < raiz->valor)
        {
            raiz->esq = remover(raiz->esq, valor);
        }
        else
        {
            raiz->dir = remover(raiz->dir, valor);
        }
    }
    return raiz;
}

int altura(arvore raiz)
{
    if (raiz == NULL)
        return -1;
    else
    {
        int he = altura(raiz->esq);
        int hd = altura(raiz->dir);
        if (he < hd)
            return hd + 1;
        else
            return he + 1;
    }
}