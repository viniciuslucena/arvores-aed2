#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

int main(int argc, char *argv[])
{
    arvore a;
    int opcao;
    inicializar(&a);

    while (1)
    {
        scanf("%d", &opcao);

        switch (opcao)
        {
            double valor;
            case 1:
                scanf("%d", &valor);
                adicionar(valor, &a);
                break;
            case 2:
                scanf("%d", &valor);
                remover(valor, &a);
                break;
            case 10:
                printf("%d\n", altura(a));
                break;
            case 99:
                exit(0);
        }
    }
}
