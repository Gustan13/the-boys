/*  eventos de chegada e saída utilizam o dado1 como o id de um herói
    e o dado2 como o id de um local.*/

#include <stdio.h>
#include <stdlib.h>

#include "libconjunto.h"
#include "libfila.h"
#include "liblef.h"
#include "libmundo.h"

#define FIM_DO_MUNDO 34944

int main(){
    mundo_t *mundo = cria_mundo(10, 50, 50/6, FIM_DO_MUNDO/100, 20000);
    lef_t *lef = cria_lef();
    int i;

    srand(0);
    cria_evento(10, 0, 3, 5, lef);

    /*  cria heróis */
    for (i = 0; i < mundo->nHerois; i++)
        mundo->herois[i] = cria_heroi(i, (rand() % 4) + 2, mundo);

    /*  cria locais */
    for (i = 0; i < mundo->nLocais; i++)
        mundo->locais[i] = cria_local(i, (rand() % 26) + 5, rand() % mundo->nTamanhoMundo, rand() % mundo->nTamanhoMundo, mundo);

    /*  cria eventos de chegada */
    for (i = 0; i < mundo->nHerois; i++)
        cria_evento(rand() % 96, 0, i, rand() % mundo->nLocais, lef);

    /*  cria eventos de missão  */
    for (i = 0; i < FIM_DO_MUNDO/100; i++)
        cria_evento(rand() % FIM_DO_MUNDO, 1, i, 0, lef);

    /*  cria evento de fim de mundo */
    cria_evento(FIM_DO_MUNDO, 3, 0, 0, lef);

    /*  loop principal do mundo */
    while (mundo->tempoAtual < FIM_DO_MUNDO){
        evento_t *evento_chamado = obtem_primeiro_lef(lef);
        mundo->tempoAtual = evento_chamado->tempo;
        
        switch (evento_chamado->tipo)
        {
        case 0: /*  CHEGADA */
            chegada(mundo, evento_chamado, lef);
            break;
        case 2:
            printf("O moco saiu\n");
        }
    }
    return 0;
}