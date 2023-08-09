#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "casos.h"

void liberarCasos(Caso* casos, int num_casos) {
    for (int i = 0; i < num_casos; i++) { //Loop que percorre cada caso na estrutura
        free(casos[i].poder); //Libera a memória alocada para "poder"
        free(casos[i].descricao); //Libera a memória alocada para "descricao"
    }

    free(casos); //Libera a memória alocada para o array de casos
}

Caso* criarCasos(FILE* arquivo, int num_casos) {
    Caso* casos = malloc(num_casos * sizeof(Caso)); //Aloca dinamicamente memória para um array "casos" com o tamanho "num_casos"

    for (int i = 0; i < num_casos; i++) { //Loop que percorre cada caso a ser criado
        casos[i].poder = malloc(MAX_PODER * sizeof(char)); //Aloca dinamicamente memória para armazenar a string de poder do caso atual
        casos[i].descricao = malloc(MAX_DESCR * sizeof(char)); //Aloca dinamicamente memória para armazenar a string de descrição do caso atual 
        fscanf(arquivo, "%s %s", casos[i].poder, casos[i].descricao); //Lê valores das strings de poder e descrição do caso atual
    }

    return casos; //Retorna o ponteiro "casos"
}

char* strrev2(char *str) {
      char *p1, *p2; //Ponteiros usados para percorrer a string e realizar a troca dos caracteres

      if (! str || ! *str) //Verificação para garantir que a string não seja nula ou vazia
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) //Loop que percorre a string realizando a troca dos caracteres
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str; //Retorna o ponteiro para a string após a reversão
}