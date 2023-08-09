#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "casos.h"
#include "arquivos.h"

int main(int argc, char* argv[]) {

    struct rusage r_usage; //Armazena informações sobre o uso de memória
    getrusage(RUSAGE_SELF, &r_usage);
    struct timeval start_time, end_time; //Armazena um ponto no tempo.
    gettimeofday(&start_time, NULL);

    char* nomeArquivo = argv[1]; //O valor do segundo argumento passado na linha de comando
    char* estrategia = argv[2]; //O valor do terceiro argumento passado na linha de comando

    abreArquivo(estrategia, nomeArquivo); //Abre um arquivo com base na estratégia e no nome fornecidos
    (void)argc;

    gettimeofday(&end_time, NULL); //Obtém o tempo atual e o armazena em uma variável
    double exec_time = (end_time.tv_sec - start_time.tv_sec) + 
                       (end_time.tv_usec - start_time.tv_usec) / 1000000.0; //Calcula o tempo de execução do programa, subtraindo o tempo de início
    double mem_used = r_usage.ru_maxrss / 1024.0; //Calcula a quantidade de memória utilizada pelo programa

    printf("Memória utilizada: %lf KB\n", mem_used); //Imprime a memória utilizada na execução
    printf("Tempo de execução: %lf segundos\n", exec_time); //Imprime o tempo de execução

   return 0;
}