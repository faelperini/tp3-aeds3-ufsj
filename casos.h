#ifndef _H_CASOS
#define _H_CASOS

typedef struct {
    char* poder;
    char* descricao;
} Caso;

#define MAX_DESCR 10000
#define MAX_PODER 100

void liberarCasos(Caso* casos, int num_casos);
Caso* criarCasos(FILE* arquivo, int num_casos);
char* strrev2(char *str);

#endif