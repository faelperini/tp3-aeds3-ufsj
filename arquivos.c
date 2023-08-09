#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "forcaBruta.h"
#include "KMP.h"
#include "BMH.h"
#include "casos.h"
#include "arquivos.h"

void abreArquivo(char* estrategia, char* nomeArquivo) {
    FILE* arquivoEntrada = fopen(nomeArquivo, "r"); //Abre o arquivo no modo de leitura
    if (arquivoEntrada == NULL) { //Verifica se o arquivo foi aberto com sucesso
        printf("Erro ao abrir arquivo\n"); 
        return;
    }
    int numeroTeste;
    fscanf(arquivoEntrada, "%d", &numeroTeste); //Le o valor de um número inteiro do arquivo
    imprimeResultado(arquivoEntrada, numeroTeste, estrategia, nomeArquivo); //Realiza o processamento com base nos valores lidos do arquivo.
    fclose(arquivoEntrada); //Fecha o arquivo aberto
}

void imprimeResultado(FILE* arquivo, int numeroTeste, char* estrategia, char* nomeArquivoEntrada) {
    int tamanhoNome = strlen(nomeArquivoEntrada) - 4;
    char* nomeArquivoSaida = (char*)malloc((tamanhoNome + 5) * sizeof(char));
    Caso* casos = criarCasos(arquivo, numeroTeste);

    if (nomeArquivoSaida == NULL) {
        printf("Erro ao alocar memória para o nome do arquivo de saída!\n");
        return;
    }

    strcpy(nomeArquivoSaida, nomeArquivoEntrada);
    strcpy(nomeArquivoSaida + tamanhoNome, ".out");

    FILE* arquivoSaida = fopen(nomeArquivoSaida, "a");
    if (arquivoSaida == NULL) {
        printf("Erro ao abrir o arquivo de saída!\n");
        free(nomeArquivoSaida);
        return;
    }
    for (int i = 0; i < numeroTeste; i++) { //Loop que percorre os casos de teste

        int resultado;
        if (strcmp(estrategia, "1") == 0) { //Verifica se a estratégia fornecida é igual a 1
            resultado = busca_sequenciaf(casos[i].poder, casos[i].descricao);
        } else if (strcmp(estrategia, "2") == 0) { //Verifica se a estratégia fornecida é igual a 2
            resultado = busca_sequenciaKMP(casos[i].poder, casos[i].descricao);
        } else if (strcmp(estrategia, "3") == 0) { //Verifica se a estratégia fornecida é igual a 3
            resultado = busca_sequenciaBMH(casos[i].poder, casos[i].descricao);
        } else { //Se nenhuma das condições anteriores for atendida, significa que a estratégia é inválida
            printf("Estratégia inválida!");
            return;
        }

        if (resultado != -1) { //Verifica se a sequência foi encontrada
            fprintf(arquivoSaida, "S %d\n", resultado);
        } else { //Se o resultado da busca for -1, a sequência não foi encontrada
            fprintf(arquivoSaida, "N\n");
        }
    }
    liberarCasos(casos, numeroTeste); //Libera a memória alocada para a estrutura de casos
    fclose(arquivoSaida); //Fecha o arquivo de saída
}
