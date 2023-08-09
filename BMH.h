#ifndef _H_BMH
#define _H_BMH

#include "casos.h"

void preProcess(char* pattern, int* shiftTable, int patternLength);
int BMH(char* pattern, char* text);
int busca_sequenciaBMH(char* poder, char* descricao);

#endif