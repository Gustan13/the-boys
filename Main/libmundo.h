struct heroi {
    int id;
    int paciencia;
    int idade;
    int experiencia;
    conjunto_t *habilidades;
} typedef heroi_t;

struct local {
    int id;
    int loc_max;
    conjunto_t *herois_presente;
    fila_t *fila;
    int x,y;
} typedef local_t;

struct mundo {
    int tempoAtual; 
    heroi_t *herois[1000];
    local_t *locais[1000];
    conjunto_t *habilidades;
    int nHerois;
    int nLocais;
    int nMissoes;
    int nTamanhoMundo;
} typedef mundo_t;

int cria_evento(int tempo, int tipo, int dado1, int dado2, lef_t *lef);

mundo_t *cria_mundo(int numHabilidades, int nHerois, int nLocais, int nMissoes,int nTamanhoMundo);

local_t *cria_local(int id, int loc_max, int x, int y, mundo_t *mundo);

heroi_t *cria_heroi(int id, int numHabilidades, mundo_t *mundo);

void chegada(mundo_t *mundo, evento_t *evento_chamado, lef_t *lef);

void saida(mundo_t *mundo, evento_t *evento_chamado, lef_t *lef);