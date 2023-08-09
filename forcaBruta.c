#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "casos.h"
#include "forcaBruta.h"

int busca_sequenciaf(char* poder, char* descricao) {
    int poder_len = strlen(poder); //Calcula o comprimento da string "poder"
    int descricao_len = strlen(descricao); //Calcula o comprimento da string "descricao"
    int i, j;

    for (i = 0; i < descricao_len; i++) { //Loop que percorre cada caractere na string "descricao"
        int k = i;
        int match = 1;

        for (j = 0; j < poder_len; j++) { //Loop que percorre cada caractere na string "poder"
            if (descricao[k] != poder[j]) { //Verifica se o caractere atual da "descricao" é diferente do caractere atual do "poder" 
                match = 0;
                break;
            }

            k = (k + 1) % descricao_len; //Atualiza o valor de k para avançar para o próximo caractere na "descricao"
        }

        if (match) { //Verifica se todos os caracteres do "poder" correspondem à sequência na "descricao"
            return i + 1;
        }

        match = 1;
        k = i;
        for (j = poder_len - 1; j >= 0; j--) { //Loop que percorre cada caractere na string "poder" na ordem inversa
            if (descricao[k] != poder[j]) { //Verifica se o caractere atual da "descricao" é diferente do caractere atual do "poder" 
                match = 0;
                break;
            }

            k = (k + 1) % descricao_len; //Atualiza o valor de k para avançar para o próximo caractere na "descricao"
        }

        if (match) { //Verifica se todos os caracteres do "poder" correspondem à sequência invertida na "descricao"
            return descricao_len - i;
        }
    }

    return -1; //Retorna -1 para indicar que a sequência não foi encontrada
}
