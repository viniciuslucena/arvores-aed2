#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    arvore raiz;
    int opcao, temp, chave, valor;
    float porcento;
    raiz = NULL;

    while (1 == 1)
    {
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            scanf("%d", &temp);
            raiz = inserir(raiz, temp);
            break;
        case 2:
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;
        case 10:
            printf("%d\n", altura(raiz));
            break;
        case 99:
            exit(0);
        }
    }
}
