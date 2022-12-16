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

int main()
{
    fila_t *fila = cria_fila();
    printf("hej");
    return 0;
}