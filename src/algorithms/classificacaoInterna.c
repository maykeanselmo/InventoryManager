#include "classificacaoInterna.h"
#include "../structs.h"         
#include "../file/FileUtils.h"  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <direct.h>
#include <time.h>



int classificacao_interna(FILE *arq, int M) {
    rewind(arq);

    int reg = 0, nProds = number_of_products(arq), qtdParticoes = 0, t = sizeProd();
    char nomeParticao[50];

    printf("\n\tM: %d",M);
    while (reg < nProds) {
        TProd *v[M];
        int i = 0;

        while (!feof(arq) && i < M) {
            fseek(arq, reg * t, SEEK_SET);
            v[i++] = readProd(arq);
            reg++;
        }

        if (i < M) 
            M = i;

        for (int j = 1; j < M; j++) {
            TProd *f = v[j];
            int k = j - 1;
            while (k >= 0 && v[k]->cod > f->cod) {
                v[k + 1] = v[k];
                k--;
            }
            v[k + 1] = f;
        }
        if(checkIfFolderExist("src/partitions")==false){
            _mkdir("src/partitions");
        }
        sprintf(nomeParticao, "src/partitions/partition%i.dat", qtdParticoes);
        FILE *p = fopen(nomeParticao, "wb+");
        if (p == NULL) {
            printf("Erro ao criar o arquivo de saída\n");
        }
        else{
            for (int j = 0; j < M; j++) {
                fseek(p, j * t, SEEK_SET);
                save(v[j], p);
                free(v[j]);
            }
            fclose(p);
            qtdParticoes++;
        }

    }

    printf("\nOK");
    return qtdParticoes;
}

