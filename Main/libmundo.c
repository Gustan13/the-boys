#include <stdio.h>
#include <stdlib.h>

#include "libconjunto.h"
#include "libfila.h"
#include "liblef.h"
#include "libmundo.h"

int cria_evento(int tempo, int tipo, int dado1, int dado2, lef_t *lef)
{
    evento_t *evento = malloc(sizeof(evento_t));
    if (evento == NULL)
    {
        printf("Erro na alocacao de Memoria.");
        return 0;
    }

    evento->tempo = tempo;
    evento->tipo = tipo;
    evento->dado1 = dado1;
    evento->dado2 = dado2;

    adiciona_ordem_lef(lef, evento);
    return 1;
}

mundo_t *cria_mundo(int numHabilidades, int nHerois, int nLocais, int nMissoes,int nTamanhoMundo)
{
    mundo_t *mundo = malloc(sizeof(mundo_t));
    int i;

    mundo->habilidades = cria_cjt(numHabilidades);

    for (i = 0; i < numHabilidades; i++)
        insere_cjt(mundo->habilidades, i);

    /*printf("%d\n", nHerois);*/
    mundo->nHerois = nHerois;
    mundo->nLocais = nLocais;
    mundo->nMissoes = nMissoes;
    mundo->nTamanhoMundo = nTamanhoMundo;
    mundo->tempoAtual = 0;

    for (i = 0; i < nHerois; i++)
        mundo->herois[i] = malloc(sizeof(heroi_t));

    for (i = 0; i < nLocais; i++)
        mundo->locais[i] = malloc(sizeof(local_t));

    return mundo;
}

local_t *cria_local(int id, int loc_max, int x, int y, mundo_t *mundo)
{
    local_t *local = malloc(sizeof(local_t));

    local->id = id;
    local->loc_max = loc_max;
    local->x = x;
    local->y = y;
    local->herois_presente = cria_cjt(loc_max);
    local->fila = cria_fila();

    return local;
}

heroi_t *cria_heroi(int id, int numHabilidades, mundo_t *mundo)
{
    heroi_t *heroi = malloc(sizeof(heroi_t));

    heroi->id = id;
    heroi->habilidades = cria_subcjt_cjt(mundo->habilidades, numHabilidades);
    heroi->experiencia = 0;
    heroi->paciencia = rand() % 101;
    heroi->idade = (rand() % 93) + 18;
    
    return heroi;
}

void chegada(mundo_t *mundo, evento_t *evento_chamado, lef_t *lef)
{
    if (cardinalidade_cjt(mundo->locais[evento_chamado->dado2]->herois_presente) < 
        mundo->locais[evento_chamado->dado2]->loc_max)
        {
            int TPL = (mundo->herois[evento_chamado->dado1]->paciencia) + (rand() % 9) - 2;
            insere_cjt(mundo->locais[evento_chamado->dado2]->herois_presente, evento_chamado->dado1); 
            cria_evento(mundo->tempoAtual + TPL, 2, evento_chamado->dado1, evento_chamado->dado2, lef);
            printf("%6d: CHEGA HEROI %2d Local %2d (%d/%d), ENTRA\n", mundo->tempoAtual, evento_chamado->dado1, evento_chamado->dado2,
            cardinalidade_cjt(mundo->locais[evento_chamado->dado2]->herois_presente), mundo->locais[evento_chamado->dado2]->loc_max);
        }
        else
        {
            if ((mundo->herois[evento_chamado->dado1]->paciencia/4) - tamanho_fila(mundo->locais[evento_chamado->dado2]->fila) > 0)
            {
                insere_fila(mundo->locais[evento_chamado->dado2]->fila, evento_chamado->dado1);
                printf("%6d: CHEGA HEROI %2d Local %2d (%d/%d), FILA %d\n", mundo->tempoAtual, evento_chamado->dado1, evento_chamado->dado2,
                cardinalidade_cjt(mundo->locais[evento_chamado->dado2]->herois_presente), mundo->locais[evento_chamado->dado2]->loc_max,
                tamanho_fila(mundo->locais[evento_chamado->dado2]->fila));
            }
            else
            {
                cria_evento(mundo->tempoAtual, 2, evento_chamado->dado1, evento_chamado->dado2, lef);
                printf("%6d: CHEGA HEROI %2d Local %2d (%d/%d), DESISTE\n", mundo->tempoAtual, evento_chamado->dado1, evento_chamado->dado2,
                cardinalidade_cjt(mundo->locais[evento_chamado->dado2]->herois_presente), mundo->locais[evento_chamado->dado2]->loc_max);
            }
        }
}