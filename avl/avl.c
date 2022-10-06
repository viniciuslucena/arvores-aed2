#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

void inicializar(arvore *raiz)
{
	*raiz = NULL;
}

arvore adicionar(int valor, arvore raiz, int *cresceu)
{

	if (raiz == NULL)
	{
		arvore novo = (arvore)malloc(sizeof(struct no_avl));
		novo->dado = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		novo->fb = 0;
		*cresceu = 1;
		return novo;
	}

	if (valor > raiz->dado)
	{
		raiz->dir = adicionar(valor, raiz->dir, cresceu);

		if (*cresceu)
		{

			switch (raiz->fb)
			{
			case 0:
				raiz->fb = 1;
				*cresceu = 1;
				break;
			case -1:
				raiz->fb = 0;
				*cresceu = 0;
				break;
			case 1:
				*cresceu = 0;
				return rotacionar(raiz);
			}
		}
	}
	else
	{
		raiz->esq = adicionar(valor, raiz->esq, cresceu);
		if (*cresceu)
		{
			switch (raiz->fb)
			{
			case 0:
				raiz->fb = -1;
				*cresceu = 1;
				break;
			case -1:
				*cresceu = 0;
				return rotacionar(raiz);
			case 1:
				*cresceu = 0;
				raiz->fb = 0;
				break;
			}
		}
	}

	return raiz;
}

arvore rotacionar(arvore raiz)
{
	if (raiz->fb > 0)
	{
		switch (raiz->dir->fb)
		{

		case 0:
			return rotacao_simples_esquerda(raiz);
			break;
		case 1:
			return rotacao_simples_esquerda(raiz);
			break;
		case -1:
			return rotacao_dupla_esquerda(raiz);
			break;
		}
	}
	else
	{
		switch (raiz->esq->fb)
		{
		case 0:
			return rotacao_simples_direita(raiz);
			break;
		case -1:
			return rotacao_simples_direita(raiz);
			break;
		case 1:
			return rotacao_dupla_direita(raiz);
			break;
		}
	}
}

arvore remover(int valor, arvore raiz, int *diminuiu)
{
	if (raiz == NULL)
		return NULL;

	if (raiz->dado == valor)
	{
		*diminuiu = 1;
		if (raiz->esq == NULL)
		{
			return raiz->dir;
		}
		if (raiz->dir == NULL)
		{
			return raiz->esq;
		}
		raiz->dado = maior_elemento(raiz->esq);
		raiz->esq = remover(raiz->dado, raiz->esq, diminuiu);
		if (*diminuiu)
		{
			switch (raiz->fb)
			{
			case 0:
				raiz->fb = 1;
				*diminuiu = 0;
				break;
			case -1:
				*diminuiu = 1;
				raiz->fb = 0;
				break;
			case 1:
				*diminuiu = 1;
				return rotacionar(raiz);
			}
		}
		return raiz;
	}

	if (valor > raiz->dado)
	{
		raiz->dir = remover(valor, raiz->dir, diminuiu);
		if (*diminuiu)
		{
			switch (raiz->fb)
			{
			case 0:
				raiz->fb = -1;
				*diminuiu = 0;
				break;
			case -1:
				*diminuiu = 1;
				return rotacionar(raiz);
			case 1:
				raiz->fb = 0;
				*diminuiu = 1;
				break;
			}
		}
	}
	else
	{
		raiz->esq = remover(valor, raiz->esq, diminuiu);
		if (*diminuiu)
		{
			switch (raiz->fb)
			{
			case 0:
				raiz->fb = 1;
				*diminuiu = 0;
				break;
			case -1:
				raiz->fb = 0;
				*diminuiu = 1;
				break;
			case 1:
				*diminuiu = 1;
				return rotacionar(raiz);
			}
		}
	}
	return raiz;
}

arvore rotacao_simples_esquerda(arvore raiz)
{
	arvore p, u, t1, t2, t3;

	p = raiz;
	u = raiz->dir;
	t1 = p->esq;
	t2 = u->esq;
	t3 = u->dir;

	p->dir = t2;
	u->esq = p;

	if (u->fb == 1)
	{
		p->fb = 0;
		u->fb = 0;
	}
	else
	{
		p->fb = 1;
		u->fb = -1;
	}

	return u;
}

arvore rotacao_simples_direita(arvore raiz)
{
	arvore p, u, t1, t2, t3;
	p = raiz;
	u = raiz->esq;
	t2 = u->dir;
	t1 = u->esq;
	t3 = p->dir;

	p->esq = t2;
	u->dir = p;

	if (u->fb == -1)
	{
		p->fb = 0;
		u->fb = 0;
	}
	else
	{
		p->fb = -1;
		u->fb = 1;
	}

	return u;
}

arvore rotacao_dupla_esquerda(arvore raiz)
{
	arvore p, u, v, t1, t2, t3, t4;
	p = raiz;
	u = p->dir;
	v = u->esq;
	t1 = p->esq;
	t2 = v->esq;
	t3 = v->dir;
	t4 = u->dir;

	v->esq = p;
	p->dir = t2;
	v->dir = u;
	u->esq = t3;

	switch (v->fb)
	{
	case -1:
		p->fb = 0;
		u->fb = 1;
		v->fb = 0;
		break;
	case 0:
		p->fb = 0;
		u->fb = 0;
		v->fb = 0;

		break;
	case 1:
		p->fb = -1;
		u->fb = 0;
		v->fb = 0;
		break;
	}

	return v;
}

arvore rotacao_dupla_direita(arvore raiz)
{
	arvore p, u, v, t1, t2, t3, t4;
	p = raiz;
	u = p->esq;
	v = u->dir;
	t1 = u->esq;
	t2 = v->esq;
	t3 = v->dir;
	t4 = p->dir;

	v->dir = p;
	u->dir = t2;
	v->esq = u;
	p->esq = t3;

	switch (v->fb)
	{
	case -1:
		p->fb = 1;
		v->fb = 0;
		u->fb = 0;
		break;
	case 0:
		p->fb = 0;
		u->fb = 0;
		v->fb = 0;

		break;
	case 1:
		u->fb = -1;
		v->fb = 0;
		p->fb = 0;
		break;
	}

	return v;
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