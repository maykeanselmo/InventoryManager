#include "selecaoporsubstituicao.h"
#include "../structs.h"         
#include "../file/FileUtils.h"  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <direct.h>
#include <time.h>


int selecao_por_substituicao(FILE *out, int num_p) {
    rewind(out);

    int M = num_p;
    int qtdPart = 0,contador = 0;

    TProd *prodAux;
    TProd *prods[num_p];
    char nomeParticao[50];

    for (int i = 0; i < num_p; i++) {
        prods[i] = readProd(out);
        if (prods[i] == NULL) {
            printf("Erro ao ler produto\n");
            for (int j = 0; j < i; j++) {
                free(prods[j]);
            }
            return 0;
        }
    }

    if (checkIfFolderExist("src/partitionsSN") == false) {
        _mkdir("src/partitionsSN");
    }

    while (contador < M) {
        sprintf(nomeParticao, "src/partitionsSN/partition%i.dat", qtdPart++);
        FILE *partitionF = fopen(nomeParticao, "wb+");
        if (partitionF == NULL) {
            printf("Erro ao criar o arquivo de saída\n");
            for (int i = 0; i < num_p; i++) {
                free(prods[i]);
            }
            return qtdPart;
        }

        contador++;
        while (!feof(out) && M > 0) {
            prodAux = prods[0];
            int minIndex = 0;

            for (int j = 1; j < M; j++) {
                if (prods[j]->cod < prodAux->cod) {
                    prodAux = prods[j];
                    minIndex = j;
                }
            }

            save(prodAux, partitionF);

            TProd *novoProd = readProd(out);
            if (novoProd != NULL) {
                free(prods[minIndex]);
                prods[minIndex] = novoProd;
            } else {
                free(prods[minIndex]);
                prods[minIndex] = prods[--M];
            }
        }
        fclose(partitionF);
    }

    for (int i = 0; i < M; i++) {
        free(prods[i]);
    }

    return qtdPart;
}