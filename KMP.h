#ifndef _H_KMP
#define _H_KMP

#include "casos.h"

void buildTable(char* pattern, int* table, int len);
int KMP(char* pattern, char* text);
int busca_sequenciaKMP(char* poder, char* descricao);

#endif