#include <stdio.h>
#include <stdlib.h>

#define TAM 10

typedef struct nodo_f
{
    int elem;
    struct nodo_f *prox;
} nodo_f_t;

typedef struct fila
{
    nodo_f_t *ini;
    nodo_f_t *fim;
    int tamanho;
} fila_t;

fila_t *cria_fila()
{
    fila_t *fila = malloc(sizeof(fila_t));
    fila->ini = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

fila_t *destroi_fila(fila_t *f)
{
    nodo_f_t *aux;

    while (f->ini != NULL)
    {
        aux = f->ini;
        f->ini = aux->prox;
        aux->prox = NULL;
        aux = f->ini;
    }

    free(f->fim);
    f->fim = NULL;
    free(f->ini);
    f->ini = NULL;
    free(f);
    f = NULL;
    free(aux);
    aux = NULL;
    return f;
}

int vazia_fila(fila_t *f)
{
    return f->ini == NULL;
}

int tamanho_fila(fila_t *f)
{
    return f->tamanho;
}

int inserir_fila(fila_t *f, int elemento)
{
    nodo_f_t *nodo;
    if (!(nodo = malloc(sizeof(nodo_f_t))))
        return 0;

    nodo->elem = elemento;
    nodo->prox = NULL;

    if (vazia_fila(f))
    {
        f->ini = nodo;
        f->fim = nodo;
        f->tamanho++;
        return 1;
    }

    f->fim->prox = nodo;
    f->fim = nodo;

    f->tamanho++;
    return 1;
}

int retira_fila(fila_t *f, int *elemento)
{
    nodo_f_t *aux;

    if (vazia_fila(f))
        return 0;

    *elemento = f->ini->elem;
    aux = f->ini->prox;
    f->ini->prox = NULL;
    f->ini = aux;

    if (vazia_fila(f))
        f->fim = NULL;

    return 1;
}

void imprime_fila(fila *f)
{
    printf("hej");
}

int main()
{
    fila_t *fila = cria_fila();
    int elemento;
    
    srand(10);

    printf("cria fila %d\n", vazia_fila(fila));

    for (int i = 0; i < TAM; i++)
        inserir_fila(fila, rand() % 1000);

    printf("insere na fila %d\n", vazia_fila(fila));
    printf("tamanho da fila %d\n", tamanho_fila(fila));

    retira_fila(fila, &elemento);

    fila = destroi_fila(fila);
    printf("destroi fila");
    return 0;
}