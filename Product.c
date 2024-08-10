#include "Product.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>


TProd *prod(int cod, int qtd, char *name, char *duedate, double value){
    TProd *prod = (TProd * ) malloc(sizeof(TProd));
    if (prod) memset(prod, 0, sizeof(TProd));
    prod->cod = cod;
    prod->qtd = qtd;
    strcpy(prod->name, name);
    strcpy(prod->due_date, duedate);
    prod->value = value;
    return prod;
}

// writes a product to the file at the current cursor position
void save(TProd *prod, FILE *out){
    fwrite(&prod->cod, sizeof(int), 1, out);
    fwrite(&prod->qtd, sizeof(int), 1, out);
    fwrite(prod->name, sizeof(char), sizeof(prod->name), out);
    fwrite(prod->due_date, sizeof(char), sizeof(prod->due_date), out);
    fwrite(&prod->value, sizeof(double),1,out);
}

TProd *read(FILE *in){
    TProd *prod = (TProd * ) malloc(sizeof(TProd));
    if (0 >= fread(&prod->cod, sizeof(int), 1, in)) {
        free(prod);
        return NULL;
    }
    fread(&prod->qtd, sizeof(int), 1, in);
    fread(prod->name, sizeof(char), sizeof(prod->name), in);
    fread(prod->due_date, sizeof(char), sizeof(prod->due_date), in);
    fread(&prod->value, sizeof(double), 1, in);
    return prod;
}

void printProd(TProd *prod){
    printf("\n---------------------------------------");
    printf("\nPRODUCT\t\t\t- %d -",prod->cod);
    printf("\nNAME:\t\t%s",prod->name);
    printf("\nVALUE:\t\t%4.2f",prod->value);
    printf("\nQUANTITY:\t\t- %ld -",prod->qtd);
    printf("\n---------------------------------------\n");
}

int sizeProd(){
    return sizeof(int) * 2  //cod
        + sizeof(char) * 30 //name
        + sizeof(char) * 11 //due_date
        + sizeof(double); //value
}

int number_of_products(FILE* arq){
    fseek(arq, 0, SEEK_END);
    int tam = trunc(ftell(arq) / sizeProd());
    return tam;
}

TProd *findProdSequential(int cod, FILE *arq){
    clock_t ti,tf;

    TProd *p = NULL;
    int i = 0;
    rewind(arq);
    ti = clock();
    while ((p = read(arq)) != NULL){ 
        i++;    
        if (p->cod == cod){
            tf = clock();
            printf("\nTEMPO: %f\n",(double)(tf - ti) / CLOCKS_PER_SEC);
            printf("\nCOMPARACOES BUSCA SEQUENCIAL: %d\n",i);

            return p;
        }
        free(p); 
    }
    return p;
    

}












