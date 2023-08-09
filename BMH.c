#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "casos.h"
#include "BMH.h"

void preProcess(char* pattern, int* shiftTable, int patternLength) {
    int i;
    for (i = 0; i < MAX_DESCR; i++) //Loop que percorre cada posição na tabela de deslocamento
        shiftTable[i] = patternLength; //Inicializa todas as posições da tabela de deslocamento com o valor "patternLength"
    for (i = 0; i < patternLength - 1; i++) //Loop que percorre cada caractere do padrão, exceto o último
        shiftTable[(unsigned char)pattern[i]] = patternLength - 1 - i; //Atribui a cada caractere do padrão na tabela de deslocamento o valor correspondente ao deslocamento necessário
}

int BMH(char* pattern, char* text) {
    int patternLength = strlen(pattern); //Calcula o comprimento do padrão
    int textLength = strlen(text); //Calcula o comprimento do texto
    int shiftTable[MAX_DESCR]; //Declara uma tabela de deslocamento com o tamanho "MAX_DESCR"
    preProcess(pattern, shiftTable, patternLength); //Pré-processa o padrão e preenche a tabela de deslocamento

    int i = patternLength - 1; // Inicializa o índice com o valor da última posição do padrão
    while (i < textLength) { //Loop que percorre o texto enquanto o índice for menor que o comprimento do texto
        int k = 0;
        while (k < patternLength && text[i - k] == pattern[patternLength - 1 - k]) //Loop que compara os caracteres do padrão com os caracteres
            k++;
        if (k == patternLength) //Verifica se todos os caracteres do padrão foram comparados com sucesso
            return i - patternLength + 2;

        i += shiftTable[(unsigned char)text[i]]; //Soma o deslocamento correspondente ao caractere atual do texto na tabela
    }

    return -1; //Retorna -1 se o padrão não for encontrado no texto
}

int busca_sequenciaBMH(char* poder, char* descricao) {
    int descricao_len = strlen(descricao); //Calcula o comprimento da "descrição"
    char* extended_descricao = (char*)malloc((2 * descricao_len + 1) * sizeof(char)); //Aloca memória para uma nova string com o dobro do tamanho da descrição original +1
    strcpy(extended_descricao, descricao); //Copia a descrição original para "extended_descricao"
    strcat(extended_descricao, descricao); //Concatena a descrição original a "extended_descricao"

    int resultado = BMH(poder, extended_descricao); //Chama a função BMH para buscar a sequência poder na "extended_descricao"

    if (resultado != -1) //Verifica se a busca no sentido direto encontrou uma correspondência
        return resultado;

    char* extended_descricao2 = strrev2(extended_descricao); //Inverte a string "extended_descricao"
    resultado = BMH(poder, extended_descricao2); //Chama a função BMH para buscar a sequência "poder" na "descricao" invertida

    free(extended_descricao); //Libera a memória alocada

    if (resultado != -1) //Verifica se a busca na descrição invertida encontrou uma correspondência
        return descricao_len - resultado + 1;

    return -1; //Retorna -1 se a sequência poder não for encontrada em nenhuma das buscas
}