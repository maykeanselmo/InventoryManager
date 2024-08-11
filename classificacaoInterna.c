
// #include "classificacaoInterna.h"
// #include "Product.h"
// #include <string.h>
// #include <stdlib.h>
// #include <time.h>
// #include <stdarg.h>

// int classificacao_interna(FILE *arq, int M) {
//     rewind(arq); 
//     int reg = 0;
//     int nProds = number_of_products(arq);
//     int qtdParticoes = 0;
//     int t = sizeProd();
//     char nomeParticao[20];

//     while (reg < nProds) {
//         TProd *v[M];
//         int i = 0;
//         while (i < M && reg < nProds) {
//             fseek(arq, reg * t, SEEK_SET);
//             v[i] = readProd(arq);
//             i++;
//             reg++;
//         }

//         if (i != M) {
//             M = i;
//         }

//         for (int j = 1; j < M; j++) {
//             TProd *pdct = v[j];
//             i = j - 1;
//             while (i >= 0 && v[i]->cod > pdct->cod) {
//                 v[i + 1] = v[i];
//                 i--;
//             }
//             v[i + 1] = pdct;
//         }

//         sprintf(nomeParticao, "partition%i.dat", qtdParticoes);
//         FILE *p = fopen(nomeParticao, "wb+");
//         if (p == NULL) {
//             printf("Erro criar arquivo de saida\n");
//         } else {
//             for (int i = 0; i < M; i++) {
//                 fseek(p, i * t, SEEK_SET);
//                 save(v[i], p);
//                 free(v[i]);
//             }
//             fclose(p);
//             qtdParticoes++;
//         }
//     }
//     return qtdParticoes;
// }
#include "classificacaoInterna.h"
#include "Product.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

int classificacao_interna(FILE *arq, int M) {
    rewind(arq); 
    int reg = 0;
    int nProds = number_of_products(arq);
    int qtdParticoes = 0;
    int t = sizeProd();
    char nomeParticao[20];

    while (reg < nProds) {
        TProd *v[M];
        int i = 0;
        while (i < M && reg < nProds) {
            fseek(arq, reg * t, SEEK_SET);
            v[i] = readProd(arq);
            i++;
            reg++;
        }

        if (i != M) {
            M = i;
        }

        for (int j = 1; j < M; j++) {
            TProd *pdct = v[j];
            i = j - 1;
            while (i >= 0 && v[i]->cod > pdct->cod) {
                v[i + 1] = v[i];
                i--;
            }
            v[i + 1] = pdct;
        }

        sprintf(nomeParticao, "partition%i.dat", qtdParticoes);
        FILE *p = fopen(nomeParticao, "wb+");
        if (p == NULL) {
            printf("Erro criar arquivo de saida\n");
        } else {
            for (int i = 0; i < M; i++) {
                fseek(p, i * t, SEEK_SET);
                save(v[i], p);
                free(v[i]);
            }
            fclose(p);
            qtdParticoes++;
        }
    }
    return qtdParticoes;
}
