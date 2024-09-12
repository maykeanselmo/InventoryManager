#include "selecaoporsubstituicao.h"
#include "../structs.h"         
#include "../file/FileUtils.h"  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <direct.h>
#include <time.h>

void printProductCodes(const char *fileName) {
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", fileName);
        return;
    }

    printf("\nCódigos dos produtos em %s:\n", fileName);
    TProd *prod;
    while ((prod = readProd(file)) != NULL) {
        printf("Código do produto: %d\n", prod->cod);
        free(prod);
    }

    fclose(file);
}

int selecao_por_substituicao(FILE *out, int num_p) {
    rewind(out);
    int M = num_p;
    int qtdPart = 0;
    int contador = 0;
    TProd *prodAux;
    TProd *prods[num_p];
    char nomeParticao[50];
    int congelado[num_p];
    int ultimoCodGravado = -1;

    for (int i = 0; i < num_p; i++) {
        prods[i] = NULL;
        congelado[i] = 0;
    }

    for (int i = 0; i < num_p; i++) {
        prods[i] = readProd(out);
        if (prods[i] == NULL) {
            M = i;
            break;
        }
    }

    if (!checkIfFolderExist("src/partitions")) {
        _mkdir("src/partitions");
    }

    while (M > 0) {
        sprintf(nomeParticao, "src/partitions/partition%i.dat", qtdPart++);
        FILE *partitionF = fopen(nomeParticao, "wb+");
        contador = 0;
        ultimoCodGravado = -1;

        while (contador < num_p && M > 0) {
            prodAux = NULL;
            int minIndex = -1;

            for (int j = 0; j < M; j++) {
                if (!congelado[j] && (prodAux == NULL || prods[j]->cod < prodAux->cod)) {
                    prodAux = prods[j];
                    minIndex = j;
                }
            }

            if (prodAux == NULL) {
                break;
            }

            save(prodAux, partitionF);
            ultimoCodGravado = prodAux->cod;
            free(prods[minIndex]);

            TProd *novoProd = readProd(out);
            if (novoProd != NULL) {
                prods[minIndex] = novoProd;
                if (novoProd->cod < ultimoCodGravado) {
                    congelado[minIndex] = 1;
                }
            } else {
                for (int k = minIndex; k < M - 1; k++) {
                    prods[k] = prods[k + 1];
                    congelado[k] = congelado[k + 1];
                }
                M--;
            }

            contador++;
        }

        fclose(partitionF);
        printProductCodes(nomeParticao);

        for (int i = 0; i < M; i++) {
            congelado[i] = 0;
        }
    }

    for (int i = 0; i < num_p; i++) {
        if (prods[i] != NULL) {
            free(prods[i]);
        }
    }

    return qtdPart;
}
