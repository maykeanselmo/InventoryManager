#include "../structs.h"
#include "intercalacaoBasico.h"
#include <limits.h>  // Inclua para INT_MAX
#include <stdio.h>
#include "IntercalacaoBasicaAdaptada.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

// Estrutura para armazenar produto e seu arquivo associado
typedef struct vetor {
    TProd *prod;
    FILE *f;
} TVet;

// Supondo que TProd, readProd e save são definidos em outro lugar

// Função de intercalação básica adaptada
FILE* intercalacaoBasicaAdaptada(FILE **files, int num_p, char fileName[]) {
    FILE *out = fopen("saida.dat", "wb");
    if (out == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        return NULL; // Retorna NULL em caso de erro
    }

    // Cria um array de TVet para gerenciar os arquivos e produtos
    TVet v[num_p];

    // Inicializa a estrutura TVet para cada arquivo
    for (int i = 0; i < num_p; i++) {
        v[i].f = files[i];
        if (v[i].f != NULL) {
            TProd *pdct = readProd(v[i].f);
            if (pdct == NULL) {
                v[i].prod = prod(INT_MAX, 0, "", "", 0.0);
            } else {
                v[i].prod = pdct;
            }
        } else {
            v[i].prod = prod(INT_MAX, 0, "", "", 0.0);
        }
    }

    int fim = 0;
    while (!fim) {
        int menor = INT_MAX;
        int pos_menor = -1;

        // Encontra o produto com o menor código
        for (int i = 0; i < num_p; i++) {
            if (v[i].prod->cod < menor) {
                menor = v[i].prod->cod;
                pos_menor = i;
            }
        }

        if (pos_menor == -1) {
            fim = 1;
        } else {
            // Salva o produto com o menor código no arquivo de saída
            save(v[pos_menor].prod, out);

            // Lê o próximo produto do mesmo arquivo
            TProd *pdct = readProd(v[pos_menor].f);
            if (pdct == NULL) {
                v[pos_menor].prod = prod(INT_MAX, 0, "", "", 0.0);
            } else {
                v[pos_menor].prod = pdct;
            }
        }
    }

    // Libera memória e fecha arquivos
    for (int i = 0; i < num_p; i++) {
        if (v[i].f != NULL) {
            fclose(v[i].f);
        }
        free(v[i].prod);
    }
    fclose(out);
    return  out;
}