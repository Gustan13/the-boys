#include <stdio.h>
#include <stdlib.h>
#include "libconjunto.h"

#define MAX 100

conjunto_t *cria_cjt(int max)
{
    conjunto_t *cjt = malloc(sizeof(conjunto_t));

    cjt->max = max;
    cjt->card = 0;
    cjt->v = malloc(sizeof(int) * max);

    return cjt;
}

conjunto_t *destroi_cjt(conjunto_t *c)
{
    free(c->v);
    c->v = NULL;

    free(c);
    c = NULL;

    return c;
}

int vazio_cjt(conjunto_t *c)
{
    if (c->card == 0)
        return 1;
    return 0;
}

int cardinalidade_cjt(conjunto_t *c)
{
    return c->card;
}

int insere_cjt(conjunto_t *c, int elemento)
{
    int i;

    if (c->card == c->max)
        return 0;

    for (i = 0; i < c->card; i++)
    {
        if (c->v[0] == elemento)
            return 1;
    }

    c->v[c->card] = elemento;
    c->card++;

    return 1;
}

int retira_cjt (conjunto_t *c, int elemento)
{
    int found = 0;

    int i = 0;

    for (i = 0; i < c->card; i++)
    {
        if (c->v[i] == elemento)
        {
            found = 1;
            break;
        }
    }

    if (!found)
        return 0;

    c->card--;

    if (i == c->card)
        return 1;

    for (i; i < c->card; i)
    {
        c->v[i] = c->v[i + 1];
    }

    return 1;
}

int pertence_cjt(conjunto_t *c, int elemento)
{
    int i = 0;

    for (i = 0; i < c->card; i++)
    {
        if (c->v[i] == elemento)
            return 1;
    }
    return 0;
}

int contido_cjt(conjunto_t *c1, conjunto_t *c2)
{
    int num = 0, i = 0, j = 0;

    for (i = 0; i < c1->card; i++)
    {
        for (j = 0; j < c2->card; j++)
        {
            if (c1->v[i] == c2->v[j])
                num++;
        }
    }

    if (num == c1->card)
        return 1;
    else
        return 0;
}

int sao_iguais_cjt(conjunto_t *c1, conjunto_t *c2)
{
    int i, j, num = 0;

    if (c1->card != c2->card)
        return 0;

    for (i = 0; i < c1->card; i++)
    {
        for (j = 0; j < c2->card; j++)
        {
            if (c1->v[i] == c2->v[j])
                num++;
        }
    }

    if (num == c1->card)
        return 1;
    else
        return 0;
}

conjunto_t *diferenca_cjt(conjunto_t *c1, conjunto_t *c2)
{
    conjunto_t *dif = cria_cjt(MAX);
    int i, j, num = 0;

    for (i = 0; i < c1->card; i++)
    {
        num = 0;
        for (j = 0; j < c2->card; j++)
        {
            if (c1->v[i] != c2->v[j])
                num++;
        }
        if (num == c2->card)
            insere_cjt(dif, c1->v[i]);
    }

    return dif;
}

conjunto_t *interseccao_cjt(conjunto_t *c1, conjunto_t *c2)
{
    conjunto_t *itr = cria_cjt(MAX);
    int i, j;

    for (i = 0; i < c1->card; i++)
    {
        for (j = 0; j < c2->card; j++)
        {
            if (c1->v[i] == c2->v[j])
                insere_cjt(itr, c1->v[i]);
        }
    }

    return itr;
}

conjunto_t *uniao_cjt(conjunto_t *c1, conjunto_t *c2)
{
    conjunto_t *uni = cria_cjt(MAX);
    int i, j, repetido;

    for (i = 0; i < c1->card; i++)
        insere_cjt(uni, c1->v[i]);

    for (i = 0; i < c2->card; i++) {
        repetido = 0;
        for (j = 0; j < c1->card; j++) {
            if (c2->v[i] == uni->v[j])
                repetido++;
        }
        if (!repetido)
            insere_cjt(uni, c2->v[i]);
    }

    return uni;
}

conjunto_t *copia_cjt(conjunto_t *c)
{
    conjunto_t *copia = malloc(sizeof(conjunto_t));
    int i;

    for (i = 0; i < c->card; i++)
        insere_cjt(copia, c->v[i]);

    return copia;
}

conjunto_t *cria_subcjt_cjt(conjunto_t *c, int n)
{
    conjunto_t *novo_c = cria_cjt(MAX);
    int i, rv = 0;

    if (n >= c->card)
        return c;

    for (i = 0; i < n; i++)
    {
        while (pertence_cjt(novo_c, c->v[rv]))
            rv = rand() % c->card;
        insere_cjt(novo_c, c->v[rv]);
    }

    return novo_c;
}

void imprime_cjt(conjunto_t *c)
{
    conjunto_t *cjt = cria_cjt(MAX);
    int i, j, m, a = 0, aux = 0;

    for (i = 0; i < c->card; i++)
        insere_cjt(cjt, c->v[i]);

    for (i = 0; i < cjt->card; i++)
    {
        m = a;
        for (j = a; j < cjt->card; j++)
        {
            if (cjt->v[j] < cjt->v[m])
                m = j;
        }
        aux = cjt->v[m];
        cjt->v[m] = cjt->v[a];
        cjt->v[a] = aux;
        a++;
    }

    for (i = 0; i < cjt->card; i++)
    {
        if (i < cjt->card - 1)
            printf("%d ", cjt->v[i]);
        else
            printf("%d\n", cjt->v[i]);
    }

    free(cjt);
    cjt = NULL;
}

void inicia_iterador_cjt(conjunto_t *c)
{
    c->ptr = 0;
}

int incrementa_iterador_cjt (conjunto_t *c, int *ret_iterador)
{
    if (c->ptr >= c->card)
        return 0;

    *ret_iterador = c->v[c->ptr];
    c->ptr++;

    return 1;
}

int retira_um_elemento_cjt (conjunto_t *c)
{
    int i, elem;

    i = rand() % c->card;
    elem = c->v[i];

    printf("%d", elem);

    retira_cjt(c, elem);

    return elem;
}

int main()
{
    conjunto_t *cjt = cria_cjt(MAX);
    conjunto_t *cjt2 = cria_cjt(MAX);
    printf("Conjunto criado.\n");

    srand(21);

    for (int i = -15; i < 50; i++)
        insere_cjt(cjt, i);

    for (int i = 0; i < 50; i++)
        insere_cjt(cjt2, i);

    cjt2 = cria_subcjt_cjt(cjt, 3);

    imprime_cjt(cjt2);

    printf("%d\n", retira_um_elemento_cjt(cjt2));

    cjt = destroi_cjt(cjt);
    cjt2 = destroi_cjt(cjt2);
    printf("Conjuntos destruidos.");

    return 0;
} 