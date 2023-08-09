#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "casos.h"

void buildTable(char* pattern, int* table, int len) {
    int i = 0, j = -1; //Inicializa os índices
    table[0] = -1; //Define o valor inicial da tabela

    while (i < len) { //Loop que percorre o padrão enquanto o índice "i" for menor que o comprimento "len"
        while (j >= 0 && pattern[i] != pattern[j]) //Loop que retrocede o índice j enquanto ele for maior ou igual a 0 e os caracteres forem diferentes
            j = table[j];
        i++;
        j++;
        if (i == len || pattern[i] != pattern[j]) //Verifica se o índice "i" é igual ao comprimento "len" ou se os caracteres são diferentes
            table[i] = j;
        else //Caso contrário, significa que sufixo do padrão tem um prefixo correspondente anterior
            table[i] = table[j];
    }
}

int KMP(char* pattern, char* text) {
    int m = strlen(pattern); //Calcula o comprimento do padrão
    int n = strlen(text); //Calcula o comprimento do texto
    int* table = (int*)malloc((m + 1) * sizeof(int)); //Aloca memória para a tabela de pré-processamento
    buildTable(pattern, table, m); //Constrói a tabela de pré-processamento com base no padrão

    int i = 0, j = 0; //Inicializa os índices
    while (j < n) { //Loop que percorre o texto enquanto o índice "j" for menor que o comprimento "n"
        while (i >= 0 && pattern[i] != text[j]) //Loop interno que retrocede o índice "i" enquanto ele for maior ou igual a 0 e os caracteres forem diferentes
            i = table[i];
        i++;
        j++;
        if (i == m) { //Verifica se o índice "i" é igual ao comprimento "m"
            free(table); //Libera a memória alocada para a tabela de pré-processamento
            return j - i + 1; //Retorna a posição da primeira ocorrência do padrão no texto
        }
    }

    free(table); //Libera a memória alocada para a tabela de pré-processamento
    return -1; //Retorna -1 se o padrão não for encontrado no texto
}

int busca_sequenciaKMP(char* poder, char* descricao) {
    int descricao_len = strlen(descricao); //Calcula o comprimento da descrição
    char* extended_descricao = (char*)malloc((2 * descricao_len + 1) * sizeof(char)); //Aloca memória para uma versão estendida da descrição
    strcpy(extended_descricao, descricao); //Copia a descrição original
    strcat(extended_descricao, descricao); //Concatena a descrição original com a versão estendida

    int resultado = KMP(poder, extended_descricao); //Chama a função KMP para buscar o padrão na descrição estendida

    if (resultado != -1) //Verifica se o padrão foi encontrado
        return resultado;

    
    char* extended_descricao2 = strrev2(extended_descricao); //Inverte a descrição estendida
    resultado = KMP(poder, extended_descricao2); //Chama a função KMP para buscar o padrão na descrição estendida invertida

    free(extended_descricao); //Libera a memória alocada para a descrição estendida

    if (resultado != -1) //Retorna a posição corrigida se o resultado da busca invertida for diferente de -1
        return descricao_len - resultado + 1;

    return -1; //Retorna -1 se o padrão não for encontrado na descrição
}
