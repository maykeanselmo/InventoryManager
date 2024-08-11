#include "classificacaoInterna.h"
#include "../structs.h"

// Function prototypes for the refactored functions
void load_products(FILE *arq, TProd **v, int *reg, int M);
void sort_products(TProd **v, int M);
void save_partition(TProd **v, int M, int t, char *nomeParticao);

int classificacao_interna(FILE *arq, int M) {
    rewind(arq);
    int reg = 0;
    int nProds = number_of_products(arq);
    int qtdParticoes = 0;
    int t = sizeProd();
    char nomeParticao[20];

    while (reg < nProds) {
        TProd *v[M];
        load_products(arq, v, &reg, M);

        int loadedProducts = (reg < nProds) ? M : reg % M;

        sort_products(v, loadedProducts);

        sprintf(nomeParticao, "partition%i.dat", qtdParticoes);
        save_partition(v, loadedProducts, t, nomeParticao);

        qtdParticoes++;
    }

    return qtdParticoes;
}

void load_products(FILE *arq, TProd **v, int *reg, int M) {
    int t = sizeProd();
    int i = 0;
    while (i < M && *reg < number_of_products(arq)) {
        fseek(arq, (*reg) * t, SEEK_SET);
        v[i] = readProd(arq);
        i++;
        (*reg)++;
    }
}

void sort_products(TProd **v, int M) {
    for (int j = 1; j < M; j++) {
        TProd *pdct = v[j];
        int i = j - 1;
        while (i >= 0 && v[i]->cod > pdct->cod) {
            v[i + 1] = v[i];
            i--;
        }
        v[i + 1] = pdct;
    }
}

void save_partition(TProd **v, int M, int t, char *nomeParticao) {
    FILE *p = fopen(nomeParticao, "wb+");
    if (p == NULL) {
        printf("Erro criar arquivo de saida\n");
        return;
    }

    for (int i = 0; i < M; i++) {
        fseek(p, i * t, SEEK_SET);
        save(v[i], p);
        free(v[i]);
    }

    fclose(p);
}
