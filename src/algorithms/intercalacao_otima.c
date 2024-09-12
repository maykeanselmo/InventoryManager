#include "intercalacao_otima.h"
#include "../structs.h"
#include "../file/FileUtils.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_products(const TProd *a, const TProd *b) {
    return a->cod - b->cod;
}

void intercalacao_otima(int num_particoes, const char *input_path) {
    FILE *partitions[num_particoes];
    char partitionFileName[100];
    FILE *outputFile;

    // Abrir partições
    for (int i = 0; i < num_particoes; i++) {
        sprintf(partitionFileName, "src/partitions/partition%d.dat", i);
        partitions[i] = fopen(partitionFileName, "rb");
        if (partitions[i] == NULL) {
            printf("Erro ao abrir a partição %s\n", partitionFileName);
            exit(EXIT_FAILURE);
        }
    }

    // Abrir o arquivo de saída (sobrescrever o arquivo de entrada)
    outputFile = fopen(input_path, "wb+");
    if (outputFile == NULL) {
        printf("Erro ao criar o arquivo final de saída.\n");
        exit(EXIT_FAILURE);
    }

    TProd *current_products[num_particoes];
    for (int i = 0; i < num_particoes; i++) {
        current_products[i] = readProd(partitions[i]);
        if (current_products[i] == NULL) {
            current_products[i] = malloc(sizeof(TProd));
            current_products[i]->cod = INT_MAX;
        }
    }

    while (1) {
        int minIndex = -1;
        TProd *minProduct = NULL;

        for (int i = 0; i < num_particoes; i++) {
            if (current_products[i]->cod != INT_MAX && (minIndex == -1 || compare_products(current_products[i], minProduct) < 0)) {
                minIndex = i;
                minProduct = current_products[i];
            }
        }

        if (minIndex == -1) {
            break;
        }

        save(minProduct, outputFile);

        current_products[minIndex] = readProd(partitions[minIndex]);
        if (current_products[minIndex] == NULL) {
            current_products[minIndex] = malloc(sizeof(TProd));
            current_products[minIndex]->cod = INT_MAX;
        }
    }
    fclose(outputFile);
    for (int i = 0; i < num_particoes; i++) {
        fclose(partitions[i]);
        free(current_products[i]);
    }

    printf("Intercalação ótima concluída. Arquivo final: %s\n", input_path);
}
