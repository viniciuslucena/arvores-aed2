#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

arvore no_null;

void inicializar(arvore *raiz)
{
	*raiz = NULL;
	no_null = (arvore)malloc(sizeof(struct no_rb));
	no_null->cor = DUPLO_PRETO;
	no_null->dado = 0;
	no_null->esq = NULL;
	no_null->dir = NULL;
}

void adicionar(int valor, arvore *raiz)
{
	arvore posicao, pai, novo;
	posicao = *raiz;
	pai = NULL;

	while (posicao != NULL)
	{
		pai = posicao;
		if (valor > posicao->dado)
			posicao = posicao->dir;
		else
			posicao = posicao->esq;
	}

	novo = (arvore)malloc(sizeof(struct no_rb));
	novo->dado = valor;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->pai = pai;
	novo->cor = VERMELHO;

	if (eh_raiz(novo))
		*raiz = novo;
	else
	{
		if (valor > pai->dado)
			pai->dir = novo;
		else
			pai->esq = novo;
	}

	ajustar(raiz, novo);
}

void ajustar(arvore *raiz, arvore elemento)
{
	while (cor(elemento->pai) == VERMELHO &&
		   cor(elemento) == VERMELHO)
	{
		if (cor(tio(elemento)) == VERMELHO)
		{
			tio(elemento)->cor = PRETO;
			elemento->pai->cor = PRETO;
			elemento->pai->pai->cor = VERMELHO;
			elemento = elemento->pai->pai;
			continue;
		}
		if (eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai))
		{
			rotacao_simples_direita(raiz, elemento->pai->pai);
			elemento->pai->cor = PRETO;
			elemento->pai->dir->cor = VERMELHO;
			continue;
		}
		if (eh_filho_direito(elemento) && eh_filho_direito(elemento->pai))
		{
			rotacao_simples_esquerda(raiz, elemento->pai->pai);
			elemento->pai->cor = PRETO;
			elemento->pai->esq->cor = VERMELHO;
			continue;
		}
		if (eh_filho_direito(elemento) && eh_filho_esquerdo(elemento->pai))
		{
			rotacao_simples_esquerda(raiz, elemento->pai);
			rotacao_simples_direita(raiz, elemento->pai);

			continue;
		}
		if (eh_filho_esquerdo(elemento) && eh_filho_direito(elemento->pai))
		{
			rotacao_simples_direita(raiz, elemento->pai);
			rotacao_simples_esquerda(raiz, elemento->pai);

			continue;
		}
	}
	(*raiz)->cor = PRETO;
}

void rotacao_simples_direita(arvore *raiz, arvore pivo)
{
	arvore u, t1;
	u = pivo->esq;
	t1 = u->dir;

	int posicao_pivo_esq = eh_filho_esquerdo(pivo);

	pivo->esq = t1;
	if (t1 != NULL)
		t1->pai = pivo;

	u->dir = pivo;

	u->pai = pivo->pai;
	pivo->pai = u;

	pivo->cor = VERMELHO;
	u->cor = PRETO;

	if (eh_raiz(u))
		*raiz = u;
	else
	{
		if (posicao_pivo_esq)
			u->pai->esq = u;
		else
			u->pai->dir = u;
	}
}

void rotacao_simples_esquerda(arvore *raiz, arvore pivo)
{
	arvore u, t1;
	u = pivo->dir;
	t1 = u->esq;

	int posicao_pivo_esq = eh_filho_esquerdo(pivo);

	pivo->dir = t1;
	if (t1 != NULL)
	{
		t1->pai = pivo;
	}

	u->esq = pivo;

	u->pai = pivo->pai;
	pivo->pai = u;

	pivo->cor = VERMELHO;
	u->cor = PRETO;

	if (eh_raiz(u))
	{
		*raiz = u;
	}
	else
	{
		if (posicao_pivo_esq)
			u->pai->esq = u;
		else
			u->pai->dir = u;
	}
}

void rotacao_simples_dir(arvore *raiz, arvore pivo)
{
	arvore u, t1;
	u = pivo->esq;
	t1 = u->dir;

	int posicao_pivo_esq = eh_filho_esquerdo(pivo);

	pivo->esq = t1;
	if (t1 != NULL)
		t1->pai = pivo;

	u->dir = pivo;

	u->pai = pivo->pai;
	pivo->pai = u;

	if (eh_raiz(u))
		*raiz = u;
	else
	{
		if (posicao_pivo_esq)
			u->pai->esq = u;
		else
			u->pai->dir = u;
	}
}

void rotacao_simples_esq(arvore *raiz, arvore pivo)
{
	arvore u, t1;
	u = pivo->dir;
	t1 = u->esq;

	int posicao_pivo_esq = eh_filho_esquerdo(pivo);

	pivo->dir = t1;
	if (t1 != NULL)
	{
		t1->pai = pivo;
	}

	u->esq = pivo;

	u->pai = pivo->pai;
	pivo->pai = u;

	if (eh_raiz(u))
	{
		*raiz = u;
	}
	else
	{
		if (posicao_pivo_esq)
			u->pai->esq = u;
		else
			u->pai->dir = u;
	}
}

enum cor cor(arvore elemento)
{
	enum cor c;
	if (elemento == NULL)
		c = PRETO;
	else
		c = elemento->cor;
	return c;
}
int eh_raiz(arvore elemento)
{
	return (elemento->pai == NULL);
}
int eh_filho_esquerdo(arvore elemento)
{
	return (elemento->pai != NULL && elemento == elemento->pai->esq);
}
int eh_filho_direito(arvore elemento)
{
	return (elemento->pai != NULL && elemento == elemento->pai->dir);
}
arvore tio(arvore elemento)
{
	return irmao(elemento->pai);
}

arvore irmao(arvore elemento)
{
	if (eh_filho_esquerdo(elemento))
		return elemento->pai->dir;
	else
		return elemento->pai->esq;
}

int altura(arvore raiz)
{
	if (raiz == NULL)
	{
		return 0;
	}
	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int maior_elemento(arvore raiz)
{
	if (raiz == NULL)
		return -1;
	if (raiz->dir == NULL)
		return raiz->dado;
	else
		return maior_elemento(raiz->dir);
}

int menor_elemento(arvore raiz)
{
	if (raiz == NULL)
		return -1;
	if (raiz->esq == NULL)
		return raiz->dado;
	else
		return maior_elemento(raiz->esq);
}

void remover(int valor, arvore *raiz)
{
	arvore posicao;
	posicao = *raiz;

	while (posicao != NULL)
	{
		if (valor == posicao->dado)
		{
			if (posicao->esq != NULL && posicao->dir != NULL)
			{
				posicao->dado = maior_elemento(posicao->esq);
				remover(posicao->dado, &(posicao->esq));
				break;
			}

			if (posicao->esq == NULL && posicao->dir != NULL)
			{
				posicao->dir->cor = PRETO;
				posicao->dir->pai = posicao->pai;

				if (eh_raiz(posicao))
				{
					*raiz = posicao->dir;
				}
				else
				{
					if (eh_filho_esquerdo(posicao))
					{
						posicao->pai->esq = posicao->dir;
					}
					else
					{
						posicao->pai->dir = posicao->dir;
					}
				}
				break;
			}

			if (posicao->esq != NULL && posicao->dir == NULL)
			{

				posicao->esq->cor = PRETO;
				posicao->esq->pai = posicao->pai;

				if (eh_raiz(posicao))
				{
					*raiz = posicao->esq;
				}
				else
				{
					if (eh_filho_direito(posicao))
					{
						posicao->pai->dir = posicao->esq;
					}
					else
					{
						posicao->pai->esq = posicao->esq;
					}
				}
				break;
			}

			if (posicao->esq == NULL && posicao->dir == NULL)
			{
				if (eh_raiz(posicao))
				{
					*raiz = NULL;
					break;
				}
				if (posicao->cor == VERMELHO)
				{
					if (eh_filho_esquerdo(posicao))
						posicao->pai->esq = NULL;
					else
						posicao->pai->dir = NULL;
					break;
				}
				else
				{
					no_null->pai = posicao->pai;
					if (eh_filho_esquerdo(posicao))
						posicao->pai->esq = no_null;
					else
						posicao->pai->dir = no_null;

					reajustar(raiz, no_null);
					break;
				}
			}
		}
		if (valor > posicao->dado)
			posicao = posicao->dir;
		else
			posicao = posicao->esq;
	}
}

void reajustar(arvore *raiz, arvore elemento)
{
	if (eh_raiz(elemento))
	{
		elemento->cor = PRETO;
		if (elemento == no_null)
			*raiz = NULL;
		return;
	}

	if (cor(elemento->pai) == PRETO &&
		cor(irmao(elemento)) == VERMELHO &&
		cor(irmao(elemento)->dir) == PRETO &&
		cor(irmao(elemento)->esq) == PRETO)
	{
		if (eh_filho_esquerdo(elemento))
			rotacao_simples_esquerda(raiz, elemento->pai);
		else
			rotacao_simples_direita(raiz, elemento->pai);
		elemento->pai->pai->cor = PRETO;
		elemento->pai->cor = VERMELHO;

		reajustar(raiz, elemento);
		return;
	}

	if (cor(elemento->pai) == PRETO &&
		cor(irmao(elemento)) == PRETO &&
		cor(irmao(elemento)->dir) == PRETO &&
		cor(irmao(elemento)->esq) == PRETO)
	{
		elemento->pai->cor = DUPLO_PRETO;
		irmao(elemento)->cor = VERMELHO;
		retira_duplo_preto(raiz, elemento);
		reajustar(raiz, elemento->pai);
		return;
	}

	if (cor(elemento->pai) == VERMELHO &&
		cor(irmao(elemento)) == PRETO &&
		cor(irmao(elemento)->dir) == PRETO &&
		cor(irmao(elemento)->esq) == PRETO)
	{
		elemento->pai->cor = PRETO;
		irmao(elemento)->cor = VERMELHO;
		retira_duplo_preto(raiz, elemento);
		return;
	}

	if (eh_filho_esquerdo(elemento) &&
		cor(irmao(elemento)) == PRETO &&
		cor(irmao(elemento)->dir) == PRETO &&
		cor(irmao(elemento)->esq) == VERMELHO)
	{
		rotacao_simples_direita(raiz, irmao(elemento));
		irmao(elemento)->cor = PRETO;
		irmao(elemento)->dir->cor = VERMELHO;
		reajustar(raiz, elemento);
		return;
	}

	if (eh_filho_direito(elemento) &&
		cor(irmao(elemento)) == PRETO &&
		cor(irmao(elemento)->dir) == VERMELHO &&
		cor(irmao(elemento)->esq) == PRETO)
	{
		rotacao_simples_esquerda(raiz, irmao(elemento));
		irmao(elemento)->cor = PRETO;
		irmao(elemento)->esq->cor = VERMELHO;
		reajustar(raiz, elemento);
		return;
	}

	if (eh_filho_esquerdo(elemento) &&
		cor(irmao(elemento)) == PRETO &&
		cor(irmao(elemento)->dir) == VERMELHO)
	{
		rotacao_simples_esq(raiz, elemento->pai);
		irmao(elemento->pai)->cor = PRETO;
		elemento->pai->pai->cor = elemento->pai->cor;
		elemento->pai->cor = PRETO;
		retira_duplo_preto(raiz, elemento);
		return;
	}

	if (eh_filho_direito(elemento) &&
		cor(irmao(elemento)) == PRETO &&
		cor(irmao(elemento)->esq) == VERMELHO)
	{
		rotacao_simples_dir(raiz, elemento->pai);
		irmao(elemento->pai)->cor = PRETO;
		elemento->pai->pai->cor = elemento->pai->cor;
		elemento->pai->cor = PRETO;
		retira_duplo_preto(raiz, elemento);
		return;
	}
}

void retira_duplo_preto(arvore *raiz, arvore elemento)
{
	if (elemento == no_null)
		if (eh_filho_esquerdo(elemento))
			elemento->pai->esq = NULL;
		else
			elemento->pai->dir = NULL;
	else
		elemento->cor = PRETO;
}