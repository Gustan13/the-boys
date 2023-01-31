#include <stdio.h>
#include <stdlib.h>
#include "liblef.h"

lef_t *cria_lef()
{
    lef_t *lista = malloc(sizeof(lef_t));
    lista->Primeiro = malloc(sizeof(nodo_lef_t));
    return lista;
}

lef_t *destroi_lef(lef_t *l)
{
    free(l->Primeiro);
    l->Primeiro = NULL;
    free(l);
    l = NULL;
    return l;
}

int adiciona_inicio_lef(lef_t *l, evento_t *evento)
{
    evento_t *e = malloc(sizeof(evento_t));
    nodo_lef_t *nodo = malloc(sizeof(nodo_lef_t));

    nodo->prox = l->Primeiro;
    l->Primeiro = nodo;
    nodo->evento =  e;

    e->tempo = evento->tempo;
    e->tipo = evento->tipo;
    e->dado1 = evento->dado1;
    e->dado2 = evento->dado2;

    return 1;
}

int adiciona_ordem_lef(lef_t *l, evento_t *evento)
{
    evento_t *e = malloc(sizeof(evento_t));
    nodo_lef_t *nodo = malloc(sizeof(nodo_lef_t));
    nodo_lef_t *p, *q;
    
    e->tempo = evento->tempo;
    e->tipo = evento->tipo;
    e->dado1 = evento->dado1;
    e->dado2 = evento->dado2;

    nodo->evento = e;

    p = l->Primeiro;
    q = l->Primeiro->prox;

    if (p->evento->tempo >= e->tempo || p == NULL)
    {
        l->Primeiro = nodo;
        nodo->prox = p;
        return 1;
    }    

    while (q != NULL && q->evento->tempo <= e->tempo)
    {
        p = q;
        q = q->prox;
    }
    nodo->prox = q;
    p->prox = nodo;

    return 1;
}

evento_t *obtem_primeiro_lef(lef_t *lef)
{
    evento_t *ptr;
    ptr = lef->Primeiro->evento;

    lef->Primeiro = lef->Primeiro->prox;

    return ptr;
}

/*int main()
{
    lef_t *lista = cria_lef();
    evento_t evento;
    evento_t *evento_ptr = &evento, *evento_ptr_2;

    evento.tempo = 5;

    printf("Lista criada\n");

    adiciona_inicio_lef(lista, evento_ptr);
    printf("Evento adicionado\n");

    evento_ptr_2 = obtem_primeiro_lef(lista);
    printf("%d\n", evento_ptr_2->tempo);

    lista = destroi_lef(lista);
    printf("Lista destruida\n");
    return 0;
}*/