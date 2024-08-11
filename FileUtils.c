#include "Product.h"
#include "FileUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>

void c_ordenate_database(FILE *out, int tam){
    int vet[tam];
    TProd *p;
    for(int i = 0 ; i<tam ; i++){
        vet[i] = i+1;
    }
    printf("\nGenerating a ordenated database...\n");
    for(int i = 0 ; i < tam; i++){
        //rever como quantidade do produto é gerada! 
        p = prod(vet[i],i*10,"PROD", "00/00/0000",10*i);
        save(p,out);
    }
    free(p);
}

//date mixup
void mix_up(int *vet,int MAX,int exchanges){
    srand(time(NULL));
    for (int i = 0; i <= exchanges; i++) {
        int j = rand() % (MAX-1);
        int k = rand() % (MAX-1);
        int tmp = vet[j];
        vet[j] = vet[k];
        vet[k] = tmp;
    }
}

void c_disorded_database(FILE *out, int tam, int exchanges){
    int vet[tam];
    TProd *p;
    for(int i = 0 ; i<tam ; i++){
        vet[i] = i+1;
    }
    mix_up(vet,tam,exchanges);
    printf("\nGenerating a disorded database...\n");
    for(int i = 0 ; i < tam; i++){
        p = prod(vet[i], i*10,"PROD", "00/00/0000",10*i);
        save(p,out);
    }
    free(p);
}

void printBase(FILE *out){
printf("\nPrinting database...\n");
    rewind(out);
    TProd *p;
    while ((p = readProd(out)) != NULL)
        printProd(p);
    free(p);
}

TProd *buscaBinariaPorCod(FILE *arq, int cod,int inicio, int fim){
    static int  i =0;
    i++;
    int meio = trunc((inicio+fim)/2);
    fseek(arq,sizeProd()*meio,SEEK_SET);
    TProd *f = readProd(arq);
    if (f->cod==cod){
        printf("\nNUMERO DE COMPARACOES BINARIA: %d\n",i);
        return f;
    }
    else if(cod> f->cod){
        return buscaBinariaPorCod(arq,cod, meio,fim);
    }
    else if(cod < f->cod){
        return buscaBinariaPorCod(arq,cod,inicio,meio);
    }
    
    return NULL;

}