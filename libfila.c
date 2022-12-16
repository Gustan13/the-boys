#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int chave;
    struct nodo *prox;
} nodo_t;

typedef struct fila
{
    nodo_t *ini;
    nodo_t *fim;
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
    nodo_t *aux;

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

int fila_vazia(fila_t *f)
{
    return f->ini == NULL;
}

int main()
{
    fila_t *fila = cria_fila();
    printf("cria fila %d\n", fila_vazia(fila));
    fila = destroi_fila(fila);
    printf("destroi fila\n");
    return 0;
}