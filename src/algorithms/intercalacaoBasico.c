#include "../structs.h"
#include "intercalacaoBasico.h"

void intercalacao_basica(FILE *out, int num_p) {
    typedef struct vetor {
        TProd *prod;
        FILE *f;
    } TVet;

    int fim = 0;
    int particao = 0;
    char nome[50];

    TVet v[num_p];

    for (int i = 0; i < num_p; i++) {
        sprintf(nome, "output/partition%i.dat", particao);
        v[i].f = fopen(nome, "rb");

        if (v[i].f != NULL) {
            TProd *pdct = readProd(v[i].f);
            if (pdct == NULL) {
                v[i].prod = prod(INT_MAX, 0, "", "", 0.0);
            } else {
                v[i].prod = pdct;
            }
        } else {
            fim = 1;
        }
        particao++;
    }

    while (!fim) {
        int menor = INT_MAX;
        int pos_menor = -1;

        for (int i = 0; i < num_p; i++) {
            if (v[i].prod->cod < menor) {
                menor = v[i].prod->cod;
                pos_menor = i;
            }
        }

        if (menor == INT_MAX) {
            fim = 1;
        } else {
            save(v[pos_menor].prod, out);
            TProd *pdct = readProd(v[pos_menor].f);
            if (pdct == NULL) {
                v[pos_menor].prod = prod(INT_MAX, 0, "", "", 0.0);
            } else {
                v[pos_menor].prod = pdct;
            }
        }
    }

    for (int i = 0; i < num_p; i++) {
        fclose(v[i].f);
        free(v[i].prod);
    }
}